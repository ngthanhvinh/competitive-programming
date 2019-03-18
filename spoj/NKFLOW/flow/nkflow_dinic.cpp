#include <bits/stdc++.h>
using namespace std;
const int N = 1010, INF = 1e9;

int n, m, s, t;
vector <int> G[N];
int c[N][N], f[N][N];
int d[N];
int ptr[N];

bool bfs() {
	for (int i = 1; i <= n; i++) d[i] = INF, ptr[i] = 0; d[s] = 0;
	queue <int> q; q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int v: G[u]) if (d[v] == INF && f[u][v] < c[u][v]) d[v] = d[u] + 1, q.push(v); 
	}
	return d[t] != INF;
}

void modify(int u, int v, int delta) { f[u][v] += delta; f[v][u] -= delta; }

int dfs(int u, int flow) {
	if (u == t || !flow) return flow;
	for (int &i = ptr[u]; i < G[u].size(); i++) {
		int v = G[u][i];
		if (f[u][v] >= c[u][v] || d[v] != d[u] + 1) continue;
		int nxt = dfs(v, min(flow, c[u][v]-f[u][v]));
		if (nxt) {
			modify(u, v, nxt); 
			return nxt;
		}
	}
	return 0;
} 

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	while(m--) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		c[u][v] = w;
		G[u].push_back(v); G[v].push_back(u);
	}
	while(bfs()) {
		while(dfs(s, INF));
	}
	long long maxFlow = 0;
	for (int i = 0; i < G[s].size(); i++) maxFlow += f[s][G[s][i]];
	printf("%lld\n", maxFlow);
}