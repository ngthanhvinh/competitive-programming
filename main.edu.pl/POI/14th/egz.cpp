#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int inf = 1e9;

int n, m, p, k;
int l[N], r[N];
vector <int> v[N];
int ans, already;

struct Road {
	int n; int m; int d;
} road[N];

struct FenwickTree {
	int T[N];
	FenwickTree() { for (int i = 0; i < N; ++i) T[i] = inf; }
	void upd(int x, int v) { for (; x > 0; x -= x & -x) T[x] = min(T[x], v); }
	int get(int x) { int res = inf; for (; x < N; x += x & -x) res = min(res, T[x]); return res; }
} BIT;

void solve(int dp[]) {
	BIT = FenwickTree();
	dp[n] = 0;
	BIT.upd(m, n);
	for (int i = n - 1; i >= 1; --i) {
		dp[i] = -i + BIT.get(1);
		vector < pair<int,int> > vec;
		for (int height : v[i]) {
			int cur = -i - 1 + BIT.get(height);
			dp[i] = min(dp[i], cur);
			vec.push_back(make_pair(height, cur + i));
		}

		for (auto &it : vec) BIT.upd(it.first, it.second);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> p >> k; ++m;
	for (int i = 0; i < p; ++i) {
		cin >> road[i].n >> road[i].m >> road[i].d; ++road[i].m;
	}

	for (int i = 0; i < p; ++i) {
		if (road[i].d == 0) v[road[i].n].push_back(road[i].m);
	}
	solve(r);

	for (int i = 0; i <= n; ++i) v[i].clear();
	for (int i = 0; i < p; ++i) {
		if (road[i].d == 1) v[n - road[i].n].push_back(road[i].m);
	}
	solve(l);
	for (int i = 1; i <= n / 2; ++i) swap(l[i], l[n + 1 - i]);

	// TODO
	int lef = 0;
	for (int i = 1; i <= n; ++i) if (l[i] == 0) ++lef; else break;
	int rig = n + 1;
	for (int i = n; i >= 1; --i) if (r[i] == 0) --rig; else break;
	if (lef >= rig) already = lef - rig + 1;
	// the number of streets that are initially satisfied
	for (int i = n; i >= 1; --i) {
		if (r[i] > k) break;
		int pos = upper_bound(l + 1, l + n + 1, k - r[i]) - l;
		--pos;
		if (pos == 0) continue;
		if (pos >= i) ans = max(ans, pos - i + 1);
	}

	cout << ans - already << endl;
}