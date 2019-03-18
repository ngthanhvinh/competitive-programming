#include <bits/stdc++.h>
using namespace std;

const int N = 300005;

int n, m, k, a[N];
long long dp[N][1 << 5];
vector <int> g[N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i], --a[i];

	while(m--) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int i = 1; i <= n; ++i) dp[i][1 << a[i]]++;

	for (int nbit = 2; nbit <= k; ++nbit) {
		for (int mask = 0; mask < (1 << k); ++mask) {
			if (__builtin_popcount(mask) != nbit) continue;

			for (int u = 1; u <= n; ++u) if (mask >> a[u] & 1) {
				int nmask = mask ^ (1 << a[u]);
				for (int &v : g[u]) {
					dp[u][mask] += dp[v][nmask];
				}
			}
		}
	}

	long long res = 0;
	for (int mask = 0; mask < (1 << k); ++mask) if (__builtin_popcount(mask) > 1) {
		for (int i = 1; i <= n; ++i) {
			res += dp[i][mask];
		}
	}

	cout << res << '\n';
}