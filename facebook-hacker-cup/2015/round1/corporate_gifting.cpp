#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, f[N][21];
vector<int> G[N];

inline void dfs(int u) {
	for (int i = 1; i <= 20; ++i) f[u][i] = i;
	for (int v: G[u]) {
		dfs(v);
		for (int i = 1; i <= 20; ++i) {
			int mn = 1e9;
			for (int j = 1; j <= 20; ++j) if (j != i) mn = min(mn, f[v][j]);
			f[u][i] += mn;
		}
	}
}

int solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) G[i].clear();
	for (int i = 1; i <= n; ++i) {
		int p; cin >> p; if (p) G[p].push_back(i);
	}
	dfs(1);
	int ans = 1e9;
	for (int i = 1; i <= 20; ++i) ans = min(ans, f[1][i]);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		cerr << i << endl;
		printf("Case #%d: %d\n", i, solve());
	}
}