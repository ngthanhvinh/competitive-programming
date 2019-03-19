#include <bits/stdc++.h>
using namespace std;
const int N = 1010;

int n, m;
bool E[N][N];
vector <int> G[N], le, ri;
int ans;
int mx[N], my[N];
bool check[N];

bool dfs(int u) {
	if (u == 0) return 1;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i]; if (check[v]) continue;
		check[v] = 1;
		if (dfs(my[v])) { mx[u] = v; my[v] = u; return 1; }
	}
	return 0;
}

int minCover() {
	int C_ = n+1, C = n;
	while(C != 0 && C < C_) {
		C_ = C; memset(check, 0, sizeof check);
		for (int i = 1; i <= le.size(); i++) if (mx[i] == 0) C -= dfs(i);
	}
	int cnt = 0;
	for (int i = 1; i <= le.size(); i++) if (mx[i]) cnt++;
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		E[u][v] = 1;
	}
	if (E[1][n]) ++ans, E[1][n] = 0;

	for (int i = 2; i < n; i++) if (E[1][i]) le.push_back(i);
	for (int i = 2; i < n; i++) if (E[i][n]) ri.push_back(i);
	//for (int u: le) cout << u << ' '; cout << endl;
	//for (int u: ri) cout << u << ' '; cout << endl;

	for (int i = 0; i < le.size(); i++) for (int j = 0; j < ri.size(); j++) {
		if (E[le[i]][ri[j]] || le[i]==ri[j]) G[i+1].push_back(j+1);
	}

	ans += minCover();
	cout << ans << endl;
}