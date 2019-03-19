#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n;
vector<int> G[N];
int sz[N];
long long fin[N], fout[N];

void dfs_in(int u, int p) {
	sz[u] = 1;
	for (int v : G[u]) if (v != p) {
		dfs_in(v, u);
		fin[u] += fin[v] + sz[v];
		sz[u] += sz[v];
	}
}

void dfs_out(int u, int p) {
	for (int v : G[u]) if (v != p) {
		fout[v] = fout[u] + fin[u] - fin[v] + n - sz[v] * 2;
		dfs_out(v, u);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}
	dfs_in(1,-1);
	dfs_out(1,-1);

	int ans = 1;
	for (int i = 1; i <= n; ++i) {
		if (fin[i] + fout[i] > fin[ans] + fout[ans]) {
			ans = i;
		}
	}

	cout << ans << '\n';
}