#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int mod = 1e9 + 7;

int n, m;
vector <int> g[N];
vector <int> rev[N];
int out[N];
int dp[N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		rev[v].push_back(u);
		++out[u];
	}

	queue <int> q;
	for (int i = 1; i <= n; ++i) if (out[i] == 0) q.push(i);

	while(!q.empty()) {
		int u = q.front(); q.pop();
		int mx = 0;
		for (int &v : g[u]) {
			mx = max(mx, dp[v]);
		}
		dp[u] = mx + 1;

		for (int &v : rev[u]) {
			if (--out[v] == 0) {
				q.push(v);
			}
		}
	}

	int res = 0;
	for (int i = 1; i <= n; ++i) {
		res += dp[i];
		if (res >= mod) res -= mod;
	}

	printf("%d\n", res);
}