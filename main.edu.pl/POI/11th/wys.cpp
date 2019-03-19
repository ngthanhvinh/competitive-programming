#include <bits/stdc++.h>
using namespace std;

pair<int,int> a[10005];
int n;
vector<int> z;

const int N = 200010;
struct SegmentTree {
	int T[N<<2], lz[N<<2];
	SegmentTree() { memset(T, 0, sizeof T); memset(lz, 0, sizeof lz); }

	#define mid ((l + r) >> 1)
	void push(int v, int l, int r) {
		if (l < r) lz[v << 1] += lz[v], lz[v << 1 | 1] += lz[v];
		T[v] += lz[v]; lz[v] = 0;
	}
	void upd(int v, int l, int r, int L, int R, int val) {
		push(v, l, r);
		if (l > r || R < l || L > r) return;
		if (L <= l && r <= R) { lz[v] = val; push(v, l, r); return; }
		upd(v << 1, l, mid, L, R, val); upd(v << 1 | 1, mid + 1, r, L, R, val);
		T[v] = max(T[v << 1], T[v << 1 | 1]);
	}
	int get(int v, int l, int r, int L, int R) {
		push(v, l, r);
		if (l > r || R < l || L > r) return 0;
		if (L <= l && r <= R) return T[v];
		return max(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
	}
} tr;

struct query {
	int s; int e; int coor; int type;
	query(int s=0, int e=0, int coor=0, int type=0): s(s), e(e), coor(coor), type(type) {}
	bool operator < (const query &rhs) const {
		return coor < rhs.coor || (coor == rhs.coor && type < rhs.type);
	}
};
vector<query> sweep;

int ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int k; scanf("%d", &k);
		for(int j = 0; j < k; ++j) {
			int x; scanf("%d", &x);
			if (j % 2 == 0) a[j].first = a[(j + k - 1) % k].first = x;
			else a[j].second = a[(j + k - 1) % k].second = x;
		}
		a[k] = a[0];
		for(int j = 0; j < k; ++j) {
			z.push_back(a[j].first);
		}
		for(int j = 0; j < k; ++j) {
			if(a[j].first < a[j+1].first) {
				sweep.push_back(query(a[j].first, a[j+1].first, a[j].second, +1));
			} else if (a[j].first > a[j+1].first) {
				sweep.push_back(query(a[j+1].first, a[j].first, a[j].second, -1));
			}
		}
	}

	sort(z.begin(), z.end());
	z.resize(distance(z.begin(), unique(z.begin(), z.end())));
	sort(sweep.begin(), sweep.end());

	for(int i = 0; i < sweep.size(); ) {
		int cur = sweep[i].coor;
		while(i < sweep.size() && sweep[i].coor == cur) {
			int s = lower_bound(z.begin(), z.end(), sweep[i].s) - z.begin() + 1;
			int e = lower_bound(z.begin(), z.end(), sweep[i].e) - z.begin();
			tr.upd(1, 1, N-1, s, e, sweep[i].type);
			++i;
		}
		ans = max(ans, tr.get(1, 1, N-1, 1, N-1));
	}

	printf("%d\n", ans);
}