#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

// SEGMENT TREE
long long T[N << 2], lz[N << 2];

#define mid ((l + r) >> 1)
void push(int v, int l, int r) {
	if (lz[v] == 0) return;
	if (l < r) lz[v << 1] += lz[v], lz[v << 1 | 1] += lz[v];
	T[v] += lz[v]; lz[v] = 0;
	return;
}
void upd(int v, int l, int r, int L, int R, long long val) {
	push(v, l, r);
	if (l > r || R < l || L > r) return;
	if (L <= l && r <= R) { lz[v] += val; push(v, l, r); return; }
	upd(v << 1, l, mid, L, R, val); upd(v << 1 | 1, mid + 1, r, L, R, val);
	T[v] = T[v << 1] + T[v << 1 | 1];
} 
long long get(int v, int l, int r, int pos) {
	push(v, l, r);
	if (l > r || l > pos || r < pos) return 0;
	if (l == r) return T[v];
	return get(v << 1, l, mid, pos) + get(v << 1 | 1, mid + 1, r, pos);
}
#undef mid
//------------------

struct Query { int u; int v; int w; };

int n, m;
vector<int> G[N];
int par[N][18], dep[N];
long long f[N], g[N];
int tin[N], tout[N], pos[N], TIME;
vector<Query> Q[N];

void dfs(int u, int p) {
	tin[u] = ++TIME; pos[u] = TIME;
	for (int v : G[u]) if (v != p) {
		par[v][0] = u;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
	tout[u] = TIME;
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 17; i >= 0; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
	for (int i = 17; i >= 0; --i) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
	return u == v ? u : par[u][0];
}

void solve(int u, int p) {
	for (int v : G[u]) if (v != p) solve(v, u), g[u] += f[v];
	for (int v : G[u]) if (v != p) {
		// h[v] = g[u] - f[v]
		upd(1, 1, n, tin[v], tout[v], g[u] - f[v]);
	}

	f[u] = g[u];
	for (auto &it : Q[u]) {
		int x = it.u, y = it.v, c = it.w;
		long long hx = get(1, 1, n, pos[x]);
		long long hy = get(1, 1, n, pos[y]);
		long long cur = hx + hy + g[x] + g[y] - g[u] + c;
		f[u] = max(f[u], cur);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}

	par[1][0] = 1;
	dfs(1,1);
	for (int j = 1; j < 18; ++j) for (int i = 1; i <= n; ++i) {
		par[i][j] = par[par[i][j-1]][j-1];
	}

	cin >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, w; cin >> u >> v >> w;
		int x = lca(u, v);
		Q[x].push_back({u, v, w});
	}

	solve(1,1);
	printf("%lld\n", f[1]);
}