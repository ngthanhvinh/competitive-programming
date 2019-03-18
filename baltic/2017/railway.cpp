#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n, m, k;
int f[N];
int id[N];
vector <pair<int,int> > G[N];
multiset <int> s[N];
int cnt[N];
vector<int> colors[N];

void add(int v, int pos) {
	s[pos].insert(v);
	int cur = s[pos].count(v);
	if (cur == cnt[v]) --f[pos];
	if (cur == 1) ++f[pos];
}

void dfs(int u, int p) {
	int mx = u;
	for (auto edge: G[u]) {
		int v = edge.second; if (v == p) continue;
		id[v] = edge.first; dfs(v, u);
		if (s[mx].size() < s[v].size()) mx = v;
	}
	s[u].swap(s[mx]); f[u] = f[mx];
	for (auto edge: G[u]) {
		int v = edge.second; if (v == p) continue;
		if (v != mx) {
			for (multiset<int>::iterator it = s[v].begin(); it != s[v].end(); ++it) add(*it, u);
		}
	}
	for (int color: colors[u]) add(color, u);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(make_pair(i, v)); G[v].push_back(make_pair(i, u));
	}
	for (int i = 1; i <= m; ++i) {
		int s; cin >> s; cnt[i] = s;
		while(s--) {
			int x; cin >> x; colors[x].push_back(i);
		}
	}

	dfs(1, 1);

	vector<int> ans;
	for (int i = 2; i <= n; ++i) {
		if (f[i] >= k) ans.push_back(id[i]);
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size()); for (int u: ans) printf("%d ", u); printf("\n");
}