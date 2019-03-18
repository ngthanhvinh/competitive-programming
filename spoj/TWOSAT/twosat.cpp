#include <bits/stdc++.h>
using namespace std;
const int N = 20010, M = 8010, INF = 1e9;
typedef vector <int> vi;
#define setLength(a, n, t) a = ((t*) calloc(n, sizeof(t))) + (n)/2

vector <int> *G;
int *color, *num, *low; 
// True is 2, False is 1

int n, m, Time, cnt;
stack <int> s;
bool invalid = 0;

void init() {
	setLength(G, 2 * n + 5, vector <int>);
	setLength(color, 2 * n + 5, int);
	setLength(num, 2 * n + 5, int);
	setLength(low, 2 * n + 5, int);
}

void setColor(int u, int x) {
	if (color[u] == (x^3)) invalid = 1; else color[u] = x;
	if (color[-u] == x) invalid = 1; else color[-u] = (x^3);
} 

void dfs(int u) {
	num[u] = low[u] = ++Time; s.push(u);
	for(int i = 0; i < (int)G[u].size(); i++) {
		int v = G[u][i];
		if (num[v]) low[u] = min(low[u], num[v]);
		else dfs(v), low[u] = min(low[u], low[v]);
		if (color[v] == 1) setColor(u, 1); // False
	}

	if (num[u] == low[u]) {
		int v = 0; 
		if (!color[u]) setColor(u, 2); // True 
		do {
			v = s.top(); num[v] = low[v] = 1e9;
			setColor(v, color[u]); s.pop();
		} while(u != v);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> m >> n; init();
	while(m--) {
		int u, v; cin >> u >> v;
		G[-u].push_back(v); G[-v].push_back(u);
	}
	for (int i = 1; i <= n; i++) if (!num[i]) dfs(i);
	for (int i = 1; i <= n; i++) if (!num[-i]) dfs(-i);

	if (invalid) return printf("NO\n"), 0;
	printf("YES\n");
	for (int i = 1; i <= n; i++) if (color[i] == 2) cnt++;
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++) if (color[i] == 2) printf("%d ", i);
	printf("\n");
}		