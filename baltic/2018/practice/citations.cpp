#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, a[N];
int sz[N];
long long dp[N], t[N];
vector <int> g[N];

void dfs(int u) {
	sz[u] = 1;
	for (int &v : g[u]) {
		dfs(v);
		sz[u] += sz[v];
	}

	sort(g[u].begin(), g[u].end(), [&](int x, int y) {
		return 1LL * t[x] * sz[y] < 1LL * t[y] * sz[x];
	});

	dp[u] = 0;
	t[u] = 1;
	for (int &v : g[u]) {
		dp[u] += dp[v] + 1LL * sz[v] * t[u];
		t[u] += t[v];
	}
	t[u] += a[u];
	dp[u] += t[u];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		int k; cin >> k;
		while(k--) {
			int j; cin >> j; g[i].push_back(j);
		}
	}

	dfs(1);

	cout << dp[1] << endl;
}