#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005, magic = (int) 1e9 + 1002;

int n, m, sink, source;
int c[maxn][maxn];
vector <int> G[maxn];
int d[maxn];
int f[maxn][maxn];

bool bfs() {
	for (int i = 1; i <= n; i++) d[i] = 0; d[source] = magic;
	queue <int> q; q.push(source);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = 0; i < G[u].size(); i++) {
			int v = G[u][i]; 
			if (!d[v] && c[u][v] > f[u][v]) d[v] = u, q.push(v);
		}
	}
	if(d[sink]) return true; else return false;
}

void enlarge() {
	int a = magic, u = sink, v; 
	while(u != source) { v = d[u]; a = min(a, c[v][u] - f[v][u]); u = v; }
	u = sink;
	while(u != source) { v = d[u]; f[v][u] += a; f[u][v] -= a; u = v; } 
}

int main() {
	scanf("%d%d%d%d", &n, &m, &source, &sink);
	while(m--) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(v); G[v].push_back(u);
		c[u][v] = w; 
	}
	while(bfs()) enlarge();

	long long res = 0;
	for (int i = 0; i < G[source].size(); i++) {
		int u = G[source][i]; res += f[source][u];
	}
	printf("%lld\n", res);
}