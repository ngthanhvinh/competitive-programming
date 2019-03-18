#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
const int N = 1e5 + 5;
int s, e, x, y, p, n, m, d[2][N], k, ans[N], per[N], in[N], out[N];
bool rem[N];
vector <int> G[N], L[N];
void bfs(int S, int cur) {
#define D d[cur]
	queue <int> q;
	q.push(S); D[S] = 1;
	while (q.size()) {
		int u = q.front(); q.pop(); if (rem[u] == 1) continue;
		for (int i = 0; i < G[u].size(); ++ i) {
			int v = G[u][i];
			if (D[v] > D[u]) {
				if (cur == 0) 
					++ in[v];
				if (cur == 1) 
					++ out[v];
				if (D[v] > D[u] + 1) {
					D[v] = D[u] + 1;
					q.push(v);
				}
			}
		}
	}
#undef D
}
void rmv(int u) {
	if(rem[u] != 0) return;
	if ((in[u] == 0 || out[u] == 0) && u != s && u != e) {
		rem[u] = 1;
		for (int i = 0; i < G[u].size(); ++ i) { 
			int v = G[u][i];
			if (d[0][v] - d[0][u] == 1) {
				-- in[v];
				rmv(v);
			} else if (d[0][u] - d[0][v] == 1) {
				-- out[v];
				rmv(v);
			}
		}
	}
}
int main() {
	memset(d, 61, sizeof(d));
	cin >> n >> m >> s >> e;
	for (int i = 0; i < m; ++ i) {
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	bfs(s, 0);
	bfs(e, 1);
	k = d[0][e];
	for (int i = 1; i <= k; ++ i)
		cin >> per[i];
	for (int i = 1; i <= n; ++ i)
		if (d[0][i] + d[1][i] > k + 1) { rem[i] = 1; }
	for (int i = 1; i <= n; ++ i) {
		if (rem[i]) 
			continue;
		L[d[0][i]].push_back(i);
	}
	for (int i = 1; i <= k; ++ i) {
		sort(L[i].begin(), L[i].end());
		L[i].resize(unique(L[i].begin(), L[i].end()) - L[i].begin());
	}
	for (int i = 1; i <= k; ++ i) {
		int len = per[i];
		for (int j = 0; j < L[len].size(); ++ j) {
			if (rem[L[len][j]] == 1) continue;
			if (ans[len] == 0) {
				ans[len] = L[len][j];
				continue;
			}
			in[L[len][j]] = 0; out[L[len][j]] = 0;
			rmv(L[len][j]);
		}
	}
	for (int i = 1; i <= k; ++ i)
		cout << ans[i] << ' ';
}