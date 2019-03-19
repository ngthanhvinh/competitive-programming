#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
typedef pair<int,int> ii;
#define fi first
#define se second

const int N = 100010, M = 200010;

int n, m, par[N];
vector <ii> G[N];
vector <ii> e;
int low[N], num[N], dfsStep;
int isBr[M];
int check[N];

void dfs(int u, int p) {
	low[u] = num[u] = ++dfsStep;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i].se, id = G[u][i].fi; if (v == p) continue; 
		if (num[v]) low[u] = min(low[u], num[v]);
		else {
			par[v] = u; dfs(v, u); low[u] = min(low[u], low[v]);
			if (low[v] >= num[v]) isBr[id] = 1;
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);

	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(ii(i, v)); G[v].push_back(ii(i, u));
		e.push_back(ii(u, v));
	}

	for (int i = 1; i <= n; ++i) if (!num[i]) dfs(i,i);

	for (int i = 1; i <= m; ++i) if (!isBr[i]) {
		int u = e[i-1].fi, v = e[i-1].se;
		if (num[u] > num[v]) swap(u,v);
		if (u == par[v]) check[u] = v; else check[v] = u;
	} 

	queue <int> q;
	for (int i = 1; i <= n; ++i) if (check[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < G[u].size(); ++i) {
			int v = G[u][i].se; if (!check[v]) check[v] = u, q.push(v);
		}
	}
	for (int i = 1; i <= n; ++i) if (!check[i]) return printf("NIE\n"), 0;
	printf("TAK\n");
	for (int i = 1; i <= n; ++i) printf("%d\n", check[i]);
}