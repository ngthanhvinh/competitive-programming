#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 200005;

struct Point {
	ll x; ll y;
	void rot() {
		ll newX = x - y, newY = x + y;
		x = newX; y = newY;
	}
} a[N], lamp, res;

int n, d;

struct SegmentTree {
	int T[N << 2], cnt[N << 2];

	void reset() {
		memset(T, 0, sizeof T); memset(cnt, 0, sizeof cnt);
	}
	#define mid ((l + r) >> 1)
	void upd(int v, int l, int r, int L, int R, int val) {
		if (l > r || R < l || L > r) return;
		if (L <= l && r <= R) {
			cnt[v] += val;
			T[v] = 0;
			if (cnt[v] > 0) T[v] = r - l + 1;
			else if (cnt[v] == 0 && l < r) T[v] = T[v << 1] + T[v << 1 | 1];
			return;
		}
		upd(v << 1, l, mid, L, R, val); upd(v << 1 | 1, mid + 1, r, L, R, val);
		T[v] = 0;
		if (cnt[v] > 0) T[v] = r - l + 1;
		else if (cnt[v] == 0 && l < r) T[v] = T[v << 1] + T[v << 1 | 1];
	}
	int find(int v, int l, int r) {
		if (l == r) return l;
		if (T[v << 1] < mid - l + 1) return find(v << 1, l, mid);
		else return find(v << 1 | 1, mid + 1, r);
	}
	#undef mid
} seg;

struct Query {
	ll x; ll y1; ll y2; ll id;
	bool operator < (const Query &rhs) const {
		return x < rhs.x || (x == rhs.x && id < rhs.id);
	}
};
vector<Query> sweep;

bool check(ll dist) {
	seg.reset(); // [lamp.y - d, lamp.y + d]
	sweep.clear();
	ll offset = lamp.y - d;
	
	for (int i = 1; i <= n; ++i) {
		ll minX = a[i].x - dist, maxX = a[i].x + dist;
		minX = max(minX, lamp.x - d);
		maxX = min(maxX, lamp.x + d);
		if (minX > maxX) continue;

		ll minY = a[i].y - dist, maxY = a[i].y + dist;
		minY = max(minY, lamp.y - d);
		maxY = min(maxY, lamp.y + d);
		if (minY > maxY) continue;

		// square: [minX...maxX][minY...maxY]
		sweep.push_back({minX, minY - offset, maxY - offset, +1});
		sweep.push_back({maxX + 1, minY - offset, maxY - offset, -1});
	}
	sort(sweep.begin(), sweep.end());

	ll coorX = 0;
	for (int i = 0; i < sweep.size(); ) {
		if (i == 0 && sweep[i].x != lamp.x - d) {
			res.x = lamp.x - d, res.y = lamp.y - d; return true;
		}

		coorX = sweep[i].x;
		while(i < sweep.size() && sweep[i].x == coorX) {
			seg.upd(1, 0, 2 * d, sweep[i].y1, sweep[i].y2, sweep[i].id);
			++i;
		}

		if (coorX != lamp.x + d + 1 && seg.T[1] < 2 * d + 1) {
			res.y = seg.find(1, 0, 2 * d) + offset;
			res.x = coorX;
			return true; 
		}
	}
	if (coorX != lamp.x + d + 1) {
		res.x = lamp.x + d, res.y = lamp.y - d; return true;
	}

	return false;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> lamp.x >> lamp.y >> d;
	lamp.rot(); // [lamp.x - d...lamp.x + d][lamp.y - d...lamp.y + d]
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].x >> a[i].y; a[i].rot();
	}
	
	ll low = 1, high = 4e10;
	while(low < high) {
		ll mid = (low + high + 1) >> 1;
		if (check(mid)) low = mid; else high = mid - 1;
	}
	check(low);
	
	ll ansX = (res.y + res.x), ansY = (res.y - res.x);
	printf("%lld %lld.%d %lld.%d\n", low + 1, ansX / 2, (ansX % 2) ? 5 : 0, ansY / 2, (ansY % 2) ? 5 : 0);
}