#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n, m, md;
bool vis[N];
vector<int> G[N];
int cnt, len;
int s[N];
int ans = 1;
int fact[N];
int X, Y;

void out() { cout << 0 << '\n'; exit(0); }

int dfs(int u, int p) {
	vis[u] = 1;
	int nchild = 0;
	int not_leaf = 0;
	for (int v : G[u]) {
		if (vis[v] == 1 && v != p) out();
		if (G[v].size() > 1) ++not_leaf;
		if (v == p) continue;
		else s[u] += dfs(v, u), ++nchild;
	}
	if (not_leaf >= 3) out();
	if (nchild == 0) return 1;
	++len;
	ans = 1LL * ans * fact[s[u]] % md;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> md;
	fact[0] = 1; 
	for (int i = 1; i < N; ++i) fact[i] = 1LL * fact[i - 1] * i % md;
	while(m--) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}

	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		if (G[i].size() == 0) { vis[i] = 1; ++X; continue; }
		if (G[i].size() == 1) continue; 
		len = 0;
		dfs(i, -1);
		++Y;
		if (len == 1) ans = 2LL * ans % md; else ans = 4LL * ans % md;
	}

	int more = 0;
	for (int i = 1; i <= n; ++i) if (G[i].size() == 1 && !vis[i]) ++more;
	more /= 2;
	Y += more;
	for (int i = 1; i <= more; ++i) ans = 2LL * ans % md;

	ans = 1LL * ans * fact[Y] % md;
	for (int i = n - X + 2; i <= n + 1; ++i) ans = 1LL * ans * i % md;

	cout << ans << '\n';
}