#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
typedef vector<int> vi;

int n, m;
vector <vi> G;
int group[N];
bool E[N][N];
bool invalid;

void dfs(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i]; 
		if (!group[v]) group[v] = 3 - group[u], dfs(v);
		else if (group[v] && group[v] != 3 - group[u]) { invalid = 1; return; }
	}
}

void solve() {
	cin >> n >> m; G.assign(n + 1, vector<int>());
	while(m--) {
		int u, v; cin >> u >> v;
		E[u][v] = E[v][u] = 1;
	}
	invalid = 0;
	memset(group, 0, sizeof group);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (i != j)
		if (!E[i][j]) G[i].push_back(j); 
		else E[i][j] = 0;
	for (int i = 1; i <= n; i++) if (!group[i]) group[i] = 1, dfs(i);

	if (invalid) cout << "NO" << endl;
	else cout << "YES" << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--)
		solve();
}