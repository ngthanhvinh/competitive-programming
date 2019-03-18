#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

int n;
vector<int> G[N];
vector<int> leaves;
int st, cnt, d[N];
vector < pair<int,int> > ans;

void dfs(int u, int p = -1) {
	d[u] = ++cnt;
	for (int i = 0; i < (int)G[u].size(); ++i) {
		int v = G[u][i]; if (v == p) continue;
		dfs(v, u);
	}
	if ((int)G[u].size() == 1) leaves.push_back(u);
}

bool cmp(int u, int v) { return d[u] < d[v]; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) if ((int)G[i].size() != 1) st = i;

	dfs(st);
	int sz = (int)leaves.size();
	sort(leaves.begin(), leaves.end(), cmp);

	for (int i = 0; i < sz / 2; ++i) {
		ans.push_back(make_pair(leaves[i], leaves[i + (sz + 1) / 2]));
	}
	if (sz % 2 == 1) ans.push_back(make_pair(leaves[(sz - 1) / 2], leaves[0]));

	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); ++i) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
}