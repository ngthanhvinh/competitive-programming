// sub 1->5, 7->8
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, H;
vector<int> z;
long long dp[N];
long long ans;

struct Data {
	int x; int y; int s; int e;
	bool operator < (const Data &rhs) const {
		return y < rhs.y;
	}
} a[N];

struct SegmentTree {
	vector< pair<int, long long> > vec[N << 2];
	// (pos, dp)

	#define mid ((l + r) >> 1)
	void add(vector< pair<int, long long> > &a, pair<int, long long> cur) {
		while(!a.empty() && a.back().second <= cur.second) a.pop_back();
		a.push_back(cur);
	}

	long long query(vector< pair<int, long long> > &a, int mn) {
		// pos >= mn
		int pos = lower_bound(a.begin(), a.end(), make_pair(mn, 0LL)) - a.begin();
		if (pos != a.size()) return a[pos].second; else return 0;
	}

	void upd(int v, int l, int r, int p, pair<int, long long> t) {
		if (l > r || l > p || r < p) return;
		add(vec[v], t);
		if (l == r) return;
		upd(v << 1, l, mid, p, t); upd(v << 1 | 1, mid + 1, r, p, t);
	}

	long long get(int v, int l, int r, int L, int R, int mn) {
		if (l > r || R < l || L > r) return 0;
		if (L <= l && r <= R) return query(vec[v], mn);
		return max(get(v << 1, l, mid, L, R, mn), get(v << 1 | 1, mid + 1, r, L, R, mn));
	}
	#undef mid

	void upd(int p, pair<int, long long> t) {
		upd(1, 0, z.size() - 1, p, t);
	}
	long long get(int l, int r, int mn) {
		return get(1, 0, z.size() - 1, l, r, mn);
	}
} seg;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> H;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].x >> a[i].y >> a[i].s >> a[i].e;
	}
	sort(a + 1, a + n + 1); // sort a[] in increasing order of y

	for (int i = 1; i <= n; ++i) {
		z.push_back(a[i].x);
	}
	sort(z.begin(), z.end()); z.erase(unique(z.begin(), z.end()), z.end());

	for (int i = 1; i <= n; ++i) {
		// a[i].x - a[i].e <= a[j].x <= a[i].x + a[i].e
		int l = lower_bound(z.begin(), z.end(), a[i].x - a[i].e) - z.begin();
		int r = upper_bound(z.begin(), z.end(), a[i].x + a[i].e) - z.begin() - 1;
		
		dp[i] = seg.get(l, r, a[i].y - a[i].e) + a[i].s; // a[j].y >= a[i].y - a[i].e
		ans = max(ans, dp[i]);
		
		int p = lower_bound(z.begin(), z.end(), a[i].x) - z.begin();
		seg.upd(p, make_pair(a[i].y, dp[i]));
	}	

	cout << ans << endl;
}