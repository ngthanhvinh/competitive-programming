#include <bits/stdc++.h>
using namespace std;
#define setLength(a, n, t) a = ((t*) calloc(n, sizeof(t))) + (n)/2

int n, m, Time;
vector <int> *G;
int *low, *num, *color;
bool invalid;
stack <int> s;

void init(int n) {
	setLength(low, 2 * n + 5, int);
	setLength(num, 2 * n + 5, int);
	setLength(color, 2 * n + 5, int);
	setLength(G, 2 * n + 5, vector<int>);
} 

void setColor(int u, int x) {
	if (color[u] == (x^3)) invalid = 1; else color[u] = x;
	if (color[-u] == x) invalid = 1; else color[-u] = (x^3); 
}

void dfs(int u) {
	num[u] = low[u] = ++Time; s.push(u);
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (num[v]) low[u] = min(low[u], num[v]);
		else dfs(v), low[u] = min(low[u], low[v]);
		if (color[v] == 1) setColor(u, 1);
	}

	if (num[u] == low[u]) {
		int v = 0; if (!color[u]) setColor(u, 2);
		do {
			v = s.top(); s.pop();
			num[v] = low[v] = 1e9;
			setColor(v, color[u]);
			//cout << v << ' ' << color[v] << endl;
		} while(u != v);
		//cout << "invalid = " << invalid << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m; int nElect = 2 * n;
	init(nElect);
	for (int i = 1; i <= n; i++) {
		G[-(2 * i - 1)].push_back(2 * i); G[-2 * i].push_back(2 * i - 1);
		G[2 * i - 1].push_back(-2 * i); G[2 * i].push_back(-(2 * i - 1));
	}
	while(m--) {
		int u, v; cin >> u >> v;
		G[v].push_back(-u); G[u].push_back(-v);
	}
	
	for (int i = 1; i <= nElect; i++) if (!num[i]) dfs(i);
	for (int i = 1; i <= nElect; i++) if (!num[-i]) dfs(-i);
	
	if (invalid) return printf("0\n"), 0;
	printf("1\n");
	for (int i = 1; i <= nElect; i++) if (color[i] == 2) printf("%d ", i);
	printf("\n");
}