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

const int INF = 1e9, N = 100010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, q;
vi sz, skip, child, pos, par, chain;
vector <vi> G;
map <ii, int> num;

void dfs(int u) {
	skip[u] = u;
	fo(i, 0, G[u].size()) {
		int v = G[u][i]; if (v == par[u]) continue;
		par[v] = u; dfs(v); child[u] += child[v];
	}
}

void hld(int u) {
	fo(i, 0, G[u].size()) {
		int v = G[u][i]; if (v == par[u]) continue;
		if (2 * child[v] >= child[u]) skip[v] = skip[u], pos[v] = sz[skip[u]] = pos[u] + 1;
		hld(v);
	}
	sz[u] = sz[skip[u]];
}

struct SegmentTree {
	vector <int> T; int size;
	SegmentTree() { T.clear(); size = 0; }
	SegmentTree(int n) { T.assign(5 * n, INF); size = n; }
	#define left id<<1
	#define right (id<<1)|1
	#define mid ((l + r) >> 1)
	void upd(int id, int l, int r, int x) {
		if (x < l || r < x || l > r) return;
		if (l == r) { if (T[id] == INF) T[id] = x; else T[id] = INF; return; }
		upd(left, l, mid, x); upd(right, mid + 1, r, x);
		T[id] = min(T[left], T[right]);
	}
	int get(int id, int l, int r, int L, int R) {
		if (R < l || L > r || l > r) return INF;
		if (L <= l && r <= R) return T[id];
		return min( get(left, l, mid, L, R) , get(right, mid + 1, r, L, R) );	
	}
	void upd(int x) { return upd(1, 1, size, x); }
	int get(int x) { return get(1, 1, size, 1, x); }
};
vector <SegmentTree> tree;

void update(int x) { tree[skip[x]].upd(pos[x]); }

int query(int x) {
	int curPos = -1, res;
	while(skip[x] != 1) {
		res = tree[skip[x]].get(pos[x]);
	//	cout << x << " chain: " << chain(x) << " pos: " << pos[x] << " res = " << res << "\n";
		if (res != INF) curPos = num[ii(skip[x], res)];
		x = par[skip[x]];
	}
	//cout << x << "\n";
	res = tree[1].get(pos[x]);
	if (res != INF) curPos = num[ii(1, res)];
	return curPos;
}

void init() {
	cin >> n >> q; 
	G.assign(n + 1, vi()); child.assign(n + 1, 1); par.assign(n + 1, 0);
	pos.assign(n + 1, 1); sz.assign(n + 1, 1); skip.assign(n + 1, 0); chain.assign(n + 1, 0);
	ff(i, 1, n - 1) {
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	dfs(1); hld(1);
	tree.assign(n + 1, SegmentTree());
	ff(i, 1, n) if (skip[i] == i) tree[i] = SegmentTree(sz[i]);
	ff(i, 1, n) num[ii(skip[i], pos[i])] = i;
}

void solve() {
	while(q--) {
		int type, x; cin >> type >> x;
		if (type) printf("%d\n", query(x));
		else update(x);
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);	
	ios_base::sync_with_stdio(false);
	init(); solve();
}