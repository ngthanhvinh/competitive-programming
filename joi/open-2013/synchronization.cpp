#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m, q;
int fr[N], to[N], state[N];
int tin[N], tout[N], TIME, dep[N], par[N][20];
vector<int> G[N];
int res[N], lst[N];

void dfs(int u) {
	tin[u] = ++TIME;
	for (int v : G[u]) {
		if (v == par[u][0]) continue;
		dep[v] = dep[u] + 1;
		par[v][0] = u;
		dfs(v);
	}
	tout[u] = TIME;
}

// SEGMENT TREE
int T[N << 2], lz[N << 2];

#define mid ((l + r) >> 1)
void push(int v, int l, int r) {
	if (lz[v] == 0) return;
	if (l < r) lz[v << 1] += lz[v], lz[v << 1 | 1] += lz[v];
	T[v] += lz[v]; lz[v] = 0;
}
void upd(int v, int l, int r, int L, int R, int val) {
	push(v, l, r);
	if (l > r || R < l || L > r) return;
	if (L <= l && r <= R) { lz[v] = val; push(v, l, r); return; }
	upd(v << 1, l, mid, L, R, val); upd(v << 1 | 1, mid + 1, r, L, R, val);
	T[v] = max(T[v << 1], T[v << 1 | 1]);
}

int get(int v, int l, int r, int pos) {
	push(v, l, r);
	if (l > r || l > pos || r < pos) return 0;
	if (l == r) return T[v];
	return max(get(v << 1, l, mid, pos), get(v << 1 | 1, mid + 1, r, pos));
}
#undef mid
// -------------------------------

int jump(int u) {
	int p = u;
	int cur = get(1, 1, n, tin[u]);
	for (int i = 17; i >= 0; --i) {
		if (get(1, 1, n, tin[par[p][i]]) - cur == dep[par[p][i]] - dep[u]) p = par[p][i];
	}
	return p;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 1; i < n; ++i) {
		cin >> fr[i] >> to[i];
		G[fr[i]].push_back(to[i]);
		G[to[i]].push_back(fr[i]);
	}
	par[1][0] = 1;
	dfs(1);
	for (int j = 1; j <= 17; ++j) {
		for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j-1]][j-1];
	}
	for (int i = 1; i < n; ++i) {
		if (dep[fr[i]] > dep[to[i]]) swap(fr[i], to[i]);
	}
	
	for (int i = 1; i <= n; ++i) res[i] = 1;
	while(m--) {
		int d; cin >> d;
		state[d] ^= 1;
		int u = fr[d], v = to[d];
		if (state[d] == 0) {
			lst[v] = res[v] = res[jump(v)];
			upd(1, 1, n, tin[v], tout[v], -1);
		} else {
			upd(1, 1, n, tin[v], tout[v], +1);
			int p = jump(u);
			res[p] = res[p] + res[v] - lst[v];
		}
	}

	for (int i = 1; i <= n; ++i) res[i] = res[jump(i)];

	while(q--) {
		int u; cin >> u;
		printf("%d\n", res[u]);
	}
}