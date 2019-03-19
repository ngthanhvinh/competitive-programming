#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int MAX = 1000010;

int n, p, w[N];
vector <int> G[N];
bitset <MAX> f[N];
int st[N], en[N], cnt, e[N];

void dfs(int u) {
	st[u] = ++cnt; e[cnt] = u;
	for (int i = 0; i < (int)G[u].size(); ++i) {
		int v = G[u][i];
		dfs(v);
	}
	en[u] = cnt;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> p;
	for (int i = 1; i <= n; ++i) {
		int par; cin >> par >> w[i];
		if (par) G[par].push_back(i);
	}

	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		dfs(i);
	}

	f[0][1] = 1;
	f[e[1]][1] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < MAX; ++j) if (f[j][i]) {
			if (j + w[e[i]] < MAX) f[j + w[e[i]]][i] = 1;
			if (en[e[i]] > i) f[j][en[e[i]]] = 1;
		}
	}	

	int ans = 0;
	for (int i = 0; i <= p; ++i) 
}