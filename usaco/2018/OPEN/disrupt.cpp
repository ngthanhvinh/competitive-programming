#include <bits/stdc++.h>
using namespace std;

const int N = 50005;

int n, m;
int par[N][17], dep[N], topar[N];
int fr[N], to[N], w[N];
vector <int> add[N], del[N];
vector < pair<int,int> > g[N];
multiset <int> ms[N];
int res[N];

void dfs(int u) {
	for (auto &e : g[u]) {
		int v = e.second, id = e.first;
		if (v == par[u][0]) continue;
		dep[v] = dep[u] + 1;
		par[v][0] = u;
		topar[v] = id;
		dfs(v);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 16; i >= 0; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
	for (int i = 16; i >= 0; --i) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
	return u == v ? u : par[u][0];
}

void solve(int u) {
	for (auto &i : add[u]) ms[u].insert(i);
	for (auto &e : g[u]) {
		int v = e.second; if (v == par[u][0]) continue;
		solve(v);
		if (ms[u].size() < ms[v].size()) ms[u].swap(ms[v]);
		for (auto &i : ms[v]) ms[u].insert(i);
	}
	for (auto &i : del[u]) ms[u].erase(ms[u].find(i));

	if (u == 1) return;

	if (ms[u].empty()) {
		res[topar[u]] = -1;
	} else {
		res[topar[u]] = (*ms[u].begin());
	}
}

int main() {
	freopen("disrupt.in", "r", stdin);
	freopen("disrupt.out", "w", stdout);
	
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		g[u].push_back(make_pair(i, v));
		g[v].push_back(make_pair(i, u));
	}

	for (int i = 1; i <= m; ++i) {
		cin >> fr[i] >> to[i] >> w[i];
	}

	par[1][0] = 1;
	dfs(1);
	for (int j = 1; j <= 16; ++j) {
		for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j - 1]][j - 1];
	}

	for (int i = 1; i <= m; ++i) {
		int x = lca(fr[i], to[i]);
		del[x].push_back(w[i]);
		del[x].push_back(w[i]);
		add[fr[i]].push_back(w[i]);
		add[to[i]].push_back(w[i]);
	}

	solve(1);

	for (int i = 1; i < n; ++i) {
		printf("%d\n", res[i]);
	}
}