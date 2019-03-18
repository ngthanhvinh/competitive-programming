#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

struct SegmentTree {
	int sz;
	vector<int> T, lz;

	SegmentTree(int sz=0) : sz(sz) {
		T.assign(4 * sz + 10, 0);
		lz.assign(4 * sz + 10, 0);
	}

	#define mid ((l + r) >> 1)

	void push(int v, int l, int r) {
		if (!lz[v]) return;
		if (l < r) lz[v << 1] ^= lz[v], lz[v << 1 | 1] ^= lz[v];
		T[v] ^= lz[v]; lz[v] = 0;
	}

	void upd(int v, int l, int r, int L, int R) {
		push(v, l, r);
		if (l > r || R < l || L > r) return;
		if (L <= l && r <= R) { lz[v] ^= 1; push(v, l, r); return; }
		upd(v << 1, l, mid, L, R); upd(v << 1 | 1, mid + 1, r, L, R);
		T[v] = max(T[v << 1], T[v << 1 | 1]);
	}

	#undef mid
} tree[N];
set<int> alive[N];

int n, par[N], cnt_black[N], ans;
vector<int> G[N], chain[N];
int skip[N], pos[N], sz[N], nchild[N];

void dfs(int u) {
	skip[u] = u; nchild[u] = 1;
	for (int v : G[u]) dfs(v), nchild[u] += nchild[v];
	pos[u] = sz[u] = 1;
}

void hld(int u) {
	for (int v : G[u]) {
		if (nchild[v] * 2 >= nchild[u]) {
			skip[v] = skip[u], pos[v] = pos[u] + 1, sz[skip[u]]++;
			chain[skip[v]].push_back(v);
		}
		hld(v);
	}
	sz[u] = sz[skip[u]];
}

bool in_chain(int u) { // u is invalid
	set<int>::iterator it = alive[skip[u]].lower_bound(pos[u] - 1);

	if (it == alive[skip[u]].end()) {
		tree[skip[u]].upd(pos[u], sz[skip[u]]); ans += sz[skip[u]] - pos[u] + 1;
		return false;
	}

	int t = (*it);
	int v = chain[skip[u]][t - 1];
	int w = chain[skip[u]][t]; // w is the direct child of v in the chain

	int wcolor = tree[skip[u]].get(t + 1);
	cnt_black[v] += wcolor == 1;

	tree[skip[u]].upd(t + 1, sz[skip[u]]); ans += sz[skip[u]] - t;
	return true; // found v
}

void add(int u) {
	// find the first vertex that is alive in the path from 0 to u
	ans = 0;
	bool found = false;

	++cnt_black[par[u]];
	if (cnt_black[par[u]] >= 2) { // can be alive
		alive[skip[par[u]]].insert(pos[par[u]]);
	}

	while(skip[u] != 0) { // u is not in the chain of 0
		found = in_chain(u);
		if (!found) {
			u = skip[u];
			// check if par[u] is valid or not
			int p = par[u];
			int ucolor = tree[u].get(1); // old color: ucolor ^ 1
			

		} else break; // already valid
	}

	if (!found) { // now u is in the same chain as 0
		in_chain(u);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &par[i]);
		G[par[i]].push_back(i);
	}

	// prepare
	dfs(0);
	hld(0);
	for (int i = 0; i <= n; ++i) if (i == skip[i]) {
		tree[i] = SegmentTree(sz[i]);
	}

	// solve
	for (int i = 1; i <= n; ++i) {
		add(i);
		printf("%d\n", ans);
	}
}