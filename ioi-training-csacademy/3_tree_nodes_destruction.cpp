#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
vector<int> G[N];
int st[N], en[N], dep[N], par[N][17], TIME;
vector< pair<int,int> > queries[N];
int ans;

// BIT
int T[N];
void upd(int x, int v) { for (; x <= n; x += x & -x) T[x] += v; }
int get(int x) { int ret = 0; for (; x > 0; x -= x & -x) ret += T[x]; return ret; }

void dfs(int u, int p) {
	st[u] = ++TIME;
	for (int v : G[u]) if (v != p) {
		dep[v] = dep[u] + 1;
		par[v][0] = u;
		dfs(v, u);
	}
	en[u] = TIME;
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 16; i >= 0; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
	for (int i = 16; i >= 0; --i) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
	return u == v ? u : par[u][0];
}

void solve(int u, int p) {
	for (int v : G[u]) if (v != p) {
		solve(v, u);
	}

	for (int i = 0; i < queries[u].size(); ++i) {
		int v1 = queries[u][i].first, v2 = queries[u][i].second;
		if (get(st[v1]) == 0 && get(st[v2]) == 0) {
			++ans;
			upd(st[u], +1);
			upd(en[u] + 1, -1);
			return;
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d %d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	par[1][0] = 1;
	dfs(1, -1);

	for (int j = 1; j < 17; ++j) {
		for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j - 1]][j - 1];
	}

	while(m--) {
		int u, v; scanf("%d %d", &u, &v);
		queries[lca(u, v)].push_back(make_pair(u, v));
	}
	solve(1, -1);

	printf("%d\n", ans);
}