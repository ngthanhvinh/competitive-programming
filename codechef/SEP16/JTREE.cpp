#include <bits/stdc++.h>
using namespace std;
const int N = 100010;

int n, m, q;
vector <int> G[N];
long long f[N];

struct Ticket {
	int k; int w;
	Ticket(int k=0, int w=0): k (k), w (w) {}
};
vector <Ticket> t[N];
int sz[N], ch[N], pos[N], skip[N], par[N][20], d[N];

void dfs(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i]; if (v == par[u][0]) continue;
		par[v][0] = u; d[v] = d[u] + 1; 
		dfs(v); ch[u] += ch[v];
	}
}

void hld(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i]; if (v == par[u][0]) continue;
		if (2 * ch[v] >= ch[u]) sz[skip[u]] = pos[v] = pos[u]+1, skip[v] = skip[u];
		hld(v);
	}
	sz[u] = sz[skip[u]];
}

struct SegmentTree {
	int size; vector <long long> T;
	SegmentTree(int _size=0) { size = _size; T.assign(4 * size + 10, (long long)1e18); }
#define le (v<<1)
#define ri ((v<<1)|1)
#define mid ((l+r)>>1)
	void upd(int v, int l, int r, int x, long long val) {
		if (l > r || l > x || r < x) return;
		if (l == r) { T[v] = val; return; }
		upd(le, l, mid, x, val); upd(ri, mid+1, r, x, val);
		T[v] = min(T[le], T[ri]);
	}
	long long get(int v, int l, int r, int L, int R) {
		if (l > r || L > r || R < l) return 1e18;
		if (L <= l && r <= R) return T[v];
		return min(get(le,l,mid,L,R), get(ri,mid+1,r,L,R));
	}
	void upd(int x, long long val) { return upd(1, 1, size, x, val); }
	long long get(int l, int r) { return get(1, 1, size, l, r); }
#undef le
#undef ri
#undef mid
} Tr[N];

int jump(int u, int k) {
	int dis = max(d[u] - k, 0); 
	for (int i = 19; i >= 0; i--) if (d[par[u][i]] >= dis) u = par[u][i];
	return u;
}

long long query(int u, int k) {
	int v = jump(u, k); u = par[u][0]; long long res = 1e18;
	while(skip[u] != skip[v]) {
		res = min(res, Tr[skip[u]].get(1, pos[u]));
		u = par[skip[u]][0];
	} 
	res = min(res, Tr[skip[u]].get(pos[v], pos[u]));
	return res;
}

void dp(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i]; 
		if (v == par[u][0]) continue;
		f[v] = (long long)1e18;
		for (int j = 0; j < t[v].size(); j++) {
			Ticket cur = t[v][j];
			f[v] = min(f[v], query(v, cur.k) + cur.w);
		}
		Tr[skip[v]].upd(pos[v], f[v]);
		dp(v);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	for (int i = 1; i <= m; i++) {
		int v, k, w; scanf("%d%d%d", &v, &k, &w);
		t[v].push_back(Ticket(k, w));
	}

	for (int i = 1; i <= n; i++) ch[i] = 1, skip[i] = i, pos[i] = 1;
	par[1][0] = 1; dfs(1);
	hld(1);
	for (int j = 1; j < 20; j++) for (int i = 1; i <= n; i++) par[i][j] = par[par[i][j-1]][j-1];
	for (int i = 1; i <= n; i++) if (skip[i] == i) Tr[i] = SegmentTree(sz[i]);	

	f[1] = 0; Tr[1].upd(1, 0);
	dp(1);

	scanf("%d", &q);
	while(q--) {
		int u; scanf("%d", &u);
		printf("%lld\n", f[u]);
	}
}