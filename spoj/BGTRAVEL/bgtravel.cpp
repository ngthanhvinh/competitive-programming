#include <bits/stdc++.h>
using namespace std;
const int N = 100010, M = 200010;
typedef pair<int,int> ii;
typedef pair<int,ii> Edge;
#define fi first
#define se second

int n, m, k;
vector <ii> adj[N];
vector <int> G[N];
vector <Edge> e;
int low[N], num[N], to[N], idx[N], step;
bool isBr[M];
int dsu[N], a[N];

// prepare and build tree
int anc(int p) { return dsu[p] == p ? p : dsu[p] = anc(dsu[p]); }
void join(int p, int q) { p = anc(p), q = anc(q); if (p != q) dsu[p] = q, a[q] += a[p], a[p] = 0; }

void findBridge(int u, int p) {
	low[u] = num[u] = ++step;
	for (int i = 0; i < adj[u].size(); ++i) {
		int v = adj[u][i].se, id = adj[u][i].fi; if (v == p) continue;
		if (num[v]) {
			low[u] = min(low[u], num[v]);
			if (to[v] == u && id != idx[v]) isBr[idx[v]] = 0;
		}
		else {
			findBridge(v, u); low[u] = min(low[u], low[v]);
			if (low[v] >= num[v]) to[v] = u, idx[v] = id, isBr[id] = 1;
		}
	}
}


// solve in the built tree (using centroid decomposition)
int d[N], sz[N];
bool del[N];
void dfs(int u, int p) {
	sz[u] = 1;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i]; if (v == p || del[v]) continue;
		d[v] = d[u] + 1; dfs(v, u); sz[u] += sz[v];
	}
}

int centroid(int u, int p, int r) {
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i]; if (v == p || del[v]) continue;
		if (2 * sz[v] > sz[r]) return centroid(v, u, r);
	}
	return u;
}

// BIT
int t[N]; long long ans;
void upd(int x, int v) { for (; x > 0; x -= x & -x) t[x] += v; }
int get(int x) { int r = 0; for (; x <= n; x += x & -x) r += t[x]; return r; }

void redfs(int u, int p, int r, int val) {
	if (val != 0) upd(d[u], val * a[u]); 
	else {
		ans += 1ll * a[u] * get(max(1, k - d[u])); 
		if (d[u] >= k) ans += 1ll * a[u] * a[r]; 
	}
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i]; if (v == p || del[v]) continue;
		redfs(v, u, r, val);
	}
}

void process(int x) {
	dfs(x, x); int u = centroid(x, x, x); 
	del[u] = 1; d[u] = 0; dfs(u, u);
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i]; if (del[v]) continue;
		redfs(v, u, u, 0);
		redfs(v, u, u, 1);
	} 
	for (int i = 0; i < G[u].size(); ++i) if (!del[G[u][i]]) redfs(G[u][i], u, u, -1);
	for (int i = 0; i < G[u].size(); ++i) if (!del[G[u][i]]) process(G[u][i]);
}

void solve() {
	for (int i = 1; i <= n; ++i) if (!del[i]) process(i);
	printf("%lld\n", ans);
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(ii(i, v)); adj[v].push_back(ii(i, u));
		e.push_back(Edge(i, ii(u, v)));
	}
	for (int i = 1; i <= n; ++i) if (!num[i]) findBridge(i,i);
	for (int i = 1; i <= n; ++i) dsu[i] = i, a[i] = 1;
	for (int i = 0; i < m; ++i) if (!isBr[e[i].fi]) join(e[i].se.fi, e[i].se.se);
	for (int i = 0; i < m; ++i) if (isBr[e[i].fi]) { int x = anc(e[i].se.fi), y = anc(e[i].se.se); G[x].push_back(y); G[y].push_back(x); }
	solve();
}