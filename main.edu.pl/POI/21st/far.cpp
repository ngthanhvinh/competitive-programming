#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n, c[N];
vector<int> G[N];
vector<int> vec[N];
long long f[N];
int ch[N];

void dfs(int u, int p) {
	ch[u] = 1;
	for(int v : G[u]) if (v != p) {
		dfs(v, u);
		ch[u] += ch[v];
		vec[u].push_back(v);
	}
	sort(vec[u].begin(), vec[u].end(), [&](int x, int y) {
		return max(f[x], ch[x] * 2 + f[y]) < max(f[y], ch[y] * 2 + f[x]);
	});

	int edges = 1;
	for (int i = 0; i < vec[u].size(); ++i) {
		int v = vec[u][i];
		f[u] = max(f[u], f[v] + edges);
		edges += 2 * ch[v];
	}

	if (u != 1) f[u] = max(f[u], (long long)c[u]);
	else f[u] = max(f[u], (long long)c[u] + (n - 1) * 2);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", c + i);
	for(int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}

	dfs(1, 1);

	printf("%lld\n", f[1]);
}