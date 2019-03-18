#include <bits/stdc++.h>
using namespace std;

#define int long long 

const int N = 260, INF = 1e9;

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
			modify(u, v, nxt); return nxt;
		}
	}
	return 0;
} 

int M[N], V[N];
long long maxFlow;

main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	s = n + 1; t = n + 2; 
	for (int i = 1; i <= n; i++) cin >> M[i], G[s].push_back(i), c[s][i] = M[i];
	for (int i = 1; i <= n; i++) cin >> V[i], G[i].push_back(t), c[i][t] = V[i];

	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
		cin >> c[i][j];
		if (c[i][j]) G[i].push_back(j);
		if (i == j) c[i][j] = INF;
	}
	
	n+=2;
	while(bfs()) 
		while(int flow = dfs(s, INF)) maxFlow += flow;

	cout << maxFlow << endl;
}