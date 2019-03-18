// http://wcipeg.com/problem/noi08p4
// Day 2, Problem 1 - Olympic Logistics

#include <bits/stdc++.h>
using namespace std;

const int N = 65;
const double inf = 1e22;

int n, m, p[N], nchild[N];
int dep[N];
vector<int> G[N];
vector<int> cyc;
double k, C[N];
double dp[N][N][N], tmp[N];
double ans;
double pw[N];

void mxm(double &x, double y) { x = (x < y) ? y : x; }

void dfs(int u) {
	nchild[u] = 1;
	// init
	for (int i = 0; i <= m; ++i) {
		for (int d = 0; d <= n; ++d) {
			dp[u][i][d] = -inf;
		}
	}
	for (int d = 0; d <= n; ++d) dp[u][0][d] = 0;
	// solve children
	for (int v : G[u]) {
		dep[v] = dep[u] + 1;
		dfs(v);
		for (int d = n; d >= 0; --d) {
			for (int i = min(m, nchild[u] + nchild[v]); i >= 0; --i) {
				for (int j = max(0, i - nchild[u]); j <= min(i, nchild[v]); ++j) {
					mxm(dp[u][i][d], max(dp[v][j][d + 1], dp[v][j][1]) + dp[u][i - j][d]);
				}
			}
		}
		nchild[u] += nchild[v];
	}

	// u itself
	for (int d = n; d >= 0; --d) {
		for (int i = min(m, nchild[u]); i >= 0; --i) {
			tmp[i] = -inf;
			if (i >= (d == 1 && p[u] != 1)) {
				tmp[i] = dp[u][i - (d == 1 && p[u] != 1)][d] + pw[d] * C[u];
			}
		}
		for (int i = min(m, nchild[u]); i >= 0; --i) {
			dp[u][i][d] = tmp[i];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) cin >> p[i];
	for (int i = 1; i <= n; ++i) cin >> C[i];

	// find cycle
	int u = 1;
	while(true) {
		u = p[u]; if (u == 1) break;
		cyc.push_back(u);
	}

	pw[0] = 1.0; for (int i = 1; i < N; ++i) pw[i] = pw[i - 1] * k;

	// When modifying a vertex i, we will always change p[i] to 1
	for (int len = 2; len <= cyc.size() + 1; ++len) {
		for (int i = 1; i <= n; ++i) G[i].clear();
		int cur = cyc[len - 2];
		int old_p = p[cur];
		p[cur] = 1;
		// now p[cur] = 1
		for (int i = 2; i <= n; ++i) G[p[i]].push_back(i);

		// dp
		dfs(1);
		double curmax = -inf;
		for (int i = 0; i <= m - (len != cyc.size() + 1); ++i) {
			curmax = max(curmax, dp[1][i][0]);
		}
		p[cur] = old_p;

		ans = max(ans, curmax / (1.0 - pw[len]));
	}

	cout << setprecision(2) << fixed << ans << endl;
}