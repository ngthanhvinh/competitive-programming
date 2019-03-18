#include <iostream>
#include <cstdio>
#include <vector>
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

struct SegmentTree {
	vector <int> mn, mx, Lazy; int size;
	SegmentTree() { mn.clear(); mx.clear(); Lazy.clear(); size = 0; }
	SegmentTree(int n) { mn.assign(5 * n, INF); mx.assign(5 * n, -INF); Lazy.assign(5 * n, 1); size = n; }
	#define left id<<1
	#define right (id<<1)|1
	#define mid ((l + r) >> 1)
	void lazy(int id, int l, int r) {
		if (Lazy[id] == 1) return;
		if (l != r) Lazy[left] *= Lazy[id], Lazy[right] *= Lazy[id];
		//lazy(left, l, mid); lazy(right, mid + 1, r);
		if (Lazy[id] == -1) { int Min = mn[id], Max = mx[id]; mx[id] = -Min, mn[id] = -Max; }
		Lazy[id] = 1;
	}

	void range_update(int id, int l, int r, int L, int R) {
		lazy(id, l, r);
		if (R < l || L > r || l > r) return;
		if (L <= l && r <= R) { Lazy[id] *= -1; lazy(id, l, r); return; }
		range_update(left, l, mid, L, R); range_update(right, mid + 1, r, L, R);
		mx[id] = max(mx[left], mx[right]); mn[id] = min(mn[left], mn[right]);
	}

	void point_update(int id, int l, int r, int x, int v) {
		lazy(id, l, r);
		if (x < l || x > r || l > r) return;
		if (l == r) { mn[id] = mx[id] = v; return; }
		point_update(left, l, mid, x, v); point_update(right, mid + 1, r, x, v);
		mx[id] = max(mx[left], mx[right]); mn[id] = min(mn[left], mn[right]);
	}

	int get(int id, int l, int r, int L, int R) {
		lazy(id, l, r);
		if (R < l || L > r || l > r) return -INF;
		if (L <= l && r <= R) return mx[id];
		return max(get(left, l, mid, L, R) , get(right, mid + 1, r, L, R));
	}
	void range_update(int l, int r) { return range_update(1, 1, size, l, r); }
	void point_update(int x, int v) { return point_update(1, 1, size, x, v); }
	int get(int l, int r) { return get(1, 1, size, l, r); } 
};

int n, par[20][N], w[N], edge;
vi l, child, sz, skip, pos;
vii E; vector <vi> G;

void prep() {
	l.assign(n + 1, 1); sz.assign(n + 1, 1); skip.assign(n + 1, 0); G.assign(n + 1, vi());
	pos.assign(n + 1, 1); child.assign(n + 1, 1); E.clear(); edge = 0; par[0][1] = 0;
}

void dfs(int u) {
	skip[u] = u;
	fo(i, 0, G[u].size()) {
		int v = G[u][i]; if (v == par[0][u]) continue;
		l[v] = l[u] + 1; par[0][v] = u; dfs(v); child[u] += child[v];
	}
}

void hld(int u) {
	fo(i, 0, G[u].size()) {
		int v = G[u][i]; if (v == par[0][u]) continue;
		if (2 * child[v] >= child[u]) skip[v] = skip[u], pos[v] = sz[skip[u]] = pos[u] + 1;
		hld(v);
	}
	sz[u] = sz[skip[u]];
}

int lca(int u, int v) {
	if (l[u] < l[v]) swap(u, v);
	fod(i, 19, 0) if (l[par[i][u]] >= l[v]) u = par[i][u];
	fod(i, 19, 0) if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
	return u == v ? u : par[0][u];
}

vector <SegmentTree> tr;

void point_update(int u, int v, int w) {
	if (v == par[0][u]) { tr[skip[u]].point_update(pos[u], w); }
	else tr[skip[v]].point_update(pos[v], w);
}
void range_update(int u, int x) { // x is one of the ancestors of u
	while(skip[u] != skip[x]) {
		tr[skip[u]].range_update(1, pos[u]);
		u = par[0][skip[u]];
	}
	if (u != x) tr[skip[x]].range_update(pos[x] + 1, pos[u]);
} 
void negatePath(int u, int v) { int x = lca(u, v); range_update(u, x); range_update(v, x); }

int get(int u, int x) { // x is one of the ancestors of u
	int res = -INF;
	while(skip[u] != skip[x]) {
		res = max(res, tr[skip[u]].get(1, pos[u]));
		u = par[0][skip[u]];
	}
	if (u != x) res = max(res, tr[skip[x]].get(pos[x] + 1, pos[u]));
	return res;
}
int query(int u, int v) { int x = lca(u, v); return max(get(u, x), get(v, x)); }

void init() {
	cin >> n; prep();
	ff(i, 1, n - 1) {
		int u, v, c; cin >> u >> v >> c;
		G[u].pb(v); G[v].pb(u);
		//cout << u << ' ' << v << "\n";
		E.pb(ii(u, v)); w[++edge] = c;
	}
	dfs(1); hld(1);
	for (int k = 1; k <= 19; ++k) for (int i = 1; i <= n; i++) par[k][i] = par[k - 1][par[k - 1][i]];
	//ff(i, 1, n) cout << i << " l = " << l[i] << " skip: " << skip[i] << " pos: " << pos[i] << " size: " << sz[i] << "\n";

	tr.assign(n + 1, SegmentTree());
	ff(i, 1, n) if (skip[i] == i) tr[i] = SegmentTree(sz[i]);
	fo(i, 0, E.size()) point_update(E[i].fi, E[i].se, w[i + 1]);
}

void solve() {
	string s; 
	while(cin >> s && s != "DONE") {
		if (s == "CHANGE") { int pos, cost; cin >> pos >> cost; point_update(E[pos - 1].fi, E[pos - 1].se, cost); }
		else if (s == "NEGATE") { int u, v; cin >> u >> v; negatePath(u, v); }
		else { int u, v; cin >> u >> v; (u == v) ? printf("0\n") : printf("%d\n", query(u, v)); }
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