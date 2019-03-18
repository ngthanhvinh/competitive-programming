#include <bits/stdc++.h>
using namespace std;

const int N = 7e4 + 5;

int n, dep[N], mn[N];
vector<int> G[N];

void dfs(int u, int p) {
	mn[u] = 1e9;
	for (int v : G[u]) if (v != p) {
		dep[v] = dep[u] + 1;
		dfs(v, u);
		mn[u] = min(mn[u], mn[v] + 1);
	}

	if (mn[u] == 1e9) mn[u] = 0; // leaf
}

int go(int u, int p, int r) {
	if (dep[u] - dep[r] >= mn[u]) return 1;

	int ret = 0;
	for (int v : G[u]) if (v != p) {
		ret += go(v, u, r);
	}
	return ret;
}

int solve(int u) {
	dep[u] = 0;
	dfs(u, u);
	return go(u, u, u);
}

int main() {
	freopen("atlarge.in", "r", stdin);
	freopen("atlarge.ans", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}

	for (int i = 1; i <= n; ++i) {
		if (G[i].size() == 1) { printf("1\n"); continue; }
		printf("%d\n", solve(i));
	}
}