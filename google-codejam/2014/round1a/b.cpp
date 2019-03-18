#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int inf = 1e6;

int n;
int ch[N];
int f[N];
vector<int> G[N];

void dfs(int u, int p) {
	ch[u] = 1;
	int sum = 0;
	vector<int> vec;
	for (int v : G[u]) if (v != p) {
		dfs(v, u), ch[u] += ch[v], vec.push_back(f[v] - ch[v]), sum += ch[v];
	}
	sort(vec.begin(), vec.end());

	f[u] = sum;
	if (vec.size() >= 2) {
		f[u] = min(f[u], sum + vec[0] + vec[1]);
	}
}

int solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) G[i].clear();
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int ans = inf;
	for (int i = 1; i <= n; ++i) {
		dfs(i, i);
		ans = min(ans, f[i]);
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: %d\n", i, solve());
	}
}