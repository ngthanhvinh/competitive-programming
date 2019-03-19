#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1000010;

int n, d[N], a[N];
vector <int> G[N];
queue <int> q;
bool vis[N];
int m, b[N];
int f[N][2]; // f[u][marked]: dp for tree
int tot;

void dfs(int u) {
	bool ok = 0, isLeaf = 1; int mx = -1e9;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i]; 
		dfs(v); isLeaf = 0;
		f[u][0] += max(f[v][0], f[v][1]); f[u][1] += max(f[v][0], f[v][1]); 
		if (f[v][0] >= f[v][1]) ok = 1; mx = max(mx, f[v][0] - f[v][1]);
	}
	if (isLeaf) return;
	if (!ok) f[u][1] += mx;
	f[u][1]++;
}

void findCycle(int u, int r) {
	vis[u] = 1; if (G[u].empty()) f[u][1] = 1; else dfs(u); 
	cerr << u << ' ' << f[u][1] << ' ' << f[u][0] << endl; int v = a[u];  
	if (v == r) return;
	else b[++m] = v, findCycle(v, r);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) { scanf("%d", &a[i]); ++d[a[i]]; }
	for (int i = 1; i <= n; ++i) if (!d[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		--d[a[u]]; G[a[u]].push_back(u);
		if (!d[a[u]]) q.push(a[u]);
	}
	for (int i = 1; i <= n; ++i) if (!vis[i] && d[i]) {
		m = 0; findCycle(i,i); int ans = 0;
		for (int mark = 0; mark < 2; ++mark) {
			vector < vector<int> > dp ( m+1, vector <int> (2, 0) );
			dp[1][mark] = f[b[1]][mark]; dp[1][1^mark] = -1e9;
			for (int i = 2; i <= m; ++i) {
				dp[i][0] = max(dp[i-1][0], dp[i-1][1]) + f[b[i]][0];
				if ((i < m) || (i == m && mark == 0)) dp[i][1] = dp[i-1][0] + f[b[i]][1];
			}
			ans = max(ans, max(dp[m][0], dp[m][1]));
		}
		tot += ans;
	}
	printf("%d\n", tot);
}