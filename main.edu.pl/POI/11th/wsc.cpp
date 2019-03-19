#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int inf = 1e9;

int n, east, west;
vector<int> G[N];
int sz[N];
int SIZE;
int dist[N];

void dfs(int u, int p) {
	sz[u] = (u >= 1 && u <= east);
	for (int v : G[u]) if (v != p) {
		dist[v] = dist[u] + 1;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

int center(int u, int p) {
	for (int v : G[u]) if (v != p && sz[v] == east) return center(v, u);
	return u;
}

int min_dist(int u, int p) {
	int nchild = 0;
	int mn = inf;
	for (int v : G[u]) if (v != p) {
		int r = min_dist(v, u);
		++nchild;
		mn = min(mn, r);
	}
	if (!nchild) return dist[u];
	return mn;
}

void solve() {
	dfs(n, -1);
	int rt = center(n, n);
	dist[rt] = 0; 
	dfs(rt, -1);

	int to = 0;
	for (int i = 0; i < G[rt].size(); ++i) {
		int v = G[rt][i]; if (sz[v] == 0) { to = v; break; }
	}

	int nTrain;
	cin >> nTrain;

	while(nTrain-- > 0) {
		int u; cin >> u; sz[++SIZE] = dist[u];
	}

	sort(sz + 1, sz + SIZE + 1);
	int cost = 0;
	int lst = 0;
	for (int i = 1; i <= SIZE; ++i) {
		int val = sz[i];
		if (val <= lst) val = lst + 1;
		lst = val;
		cost = max(cost, val);
	}
	printf("%d\n", min_dist(to, rt) + cost);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> east >> west;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}
	solve();
}