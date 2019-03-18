#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 10010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, par[20][N], w[N], edge;
vi l, sz, pos, skip, nChild;
vector <vi> G;
vector <ii> E;

void dfs(int u) {
	skip[u] = u; 
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (v != par[0][u]) {
			l[v] = l[u] + 1; par[0][v] = u; 
			dfs(v); nChild[u] += nChild[v];
		}
	}
}

int lca(int u, int v) {
	if(l[u] < l[v]) swap(u, v);
	fod(i, 19, 0) if (l[par[i][u]] >= l[v]) u = par[i][u];
	fod(i, 19, 0) if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
	return u == v ? u : par[0][u];
}

void hld(int u) {
	fo(i, 0, G[u].size()) {
		int v = G[u][i]; if (v == par[0][u]) continue;
		if (2 * nChild[v] >= nChild[u]) {
			skip[v] = skip[u]; pos[v] = pos[u] + 1; sz[skip[u]] = pos[v];
		}
		hld(v);
	}
	sz[u] = sz[skip[u]];
}

struct SegmentTree {
	vector <int> T; int size;
	SegmentTree() { T.clear(); size = 0; }
	SegmentTree(int n) { T.assign(5 * n, 0); size = n; }
	#define left id<<1
	#define right (id<<1)^1
	#define mid ((l + r) >> 1)
	void upd(int id, int l, int r, int x, int v) {
		if (x < l || r < x || l > r) return;
		if (l == r) { T[id] = v; return; }
		upd(left, l, mid, x, v); upd(right, mid + 1, r, x, v);
		T[id] = max(T[left], T[right]);
	}
	int get(int id, int l, int r, int L, int R) {
		if (R < l || L > r || l > r) return 0;
		if (L <= l && r <= R) return T[id];
		return max( get(left, l, mid, L, R) , get(right, mid + 1, r, L, R) );
	}
	void upd(int x, int v) { return upd(1, 1, size, x, v); }
	int get(int l, int r) { return get(1, 1, size, l, r); } 
};
vector <SegmentTree> tree;

void updateEdge(int u, int v, int w) {
	if (u == par[0][v]) tree[skip[v]].upd(pos[v], w);
	else tree[skip[u]].upd(pos[u], w);
}

int getMax(int u, int x) { // x is one of the ancestors of u
	int res = 0;
	while(skip[u] != skip[x] && u != x) {
		res = max(res, tree[skip[u]].get(1, pos[u]));
		u = par[0][skip[u]];
	}
	if (u != x) res = max(res, tree[skip[u]].get(pos[x] + 1, pos[u]));
	return res;
}

int query(int u, int v) { int x = lca(u, v); return max(getMax(u, x), getMax(v, x)); }

void init() {
	cin >> n; par[0][1] = edge = 0; tree.assign(n + 1, SegmentTree());
	G.assign(n + 1, vi()); pos.assign(n + 1, 1); skip.assign(n + 1, 0); 
	nChild.assign(n + 1, 1); sz.assign(n + 1, 1); l.assign(n + 1, 1); E.clear();
	ff(i, 1, n - 1) {
		int u, v, c; cin >> u >> v >> c;
		G[u].pb(v); G[v].pb(u);
		w[++edge] = c; E.pb(ii(u, v));
	}
	dfs(1); hld(1);
	//ff(i, 1, n) cout << i << " l = " << l[i] << " nChild = " << nChild[i] << " pos = " << pos[i] << " skip = " << skip[i] << " sz = " << sz[i] << "\n";
	ff(k, 1, 19) ff(i, 1, n) par[k][i] = par[k - 1][par[k - 1][i]];
	ff(i, 1, n) if (skip[i] == i) { tree[i] = SegmentTree(sz[i]); }
	fo(i, 0, E.size()) updateEdge(E[i].fi, E[i].se, w[i + 1]);
}

void solve() {
	string s;
	while(cin >> s && s != "DONE") {
		if (s == "CHANGE") { int pos, cost; cin >> pos >> cost; updateEdge(E[pos - 1].fi, E[pos - 1].se, cost); }
		else {
			int u, v; cin >> u >> v;
			printf("%d\n", query(u, v));
		}
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) {
		init();
		solve();
	}
}