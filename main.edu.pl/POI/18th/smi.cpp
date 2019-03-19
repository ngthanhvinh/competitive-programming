#include <bits/stdc++.h>
using namespace std;

int n, m;
typedef pair<int,int> ii;
vector <ii> G[100010];
bool vis[100010];
bool del[1000010];
#define prev __prev
int prev[100010];

vector <int> path;
void dfs(int u) {
	vis[u] = 1;
	while(!G[u].empty()) {
		int id = G[u].back().second, v = G[u].back().first; G[u].pop_back();
		if (del[id]) continue;
		del[id] = 1;
		dfs(v);
	}
	path.push_back(u);
}

vector < vector<int> > euler;
vector < vector<int> > ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, s, t; cin >> u >> v >> s >> t;
		if (s != t) G[u].push_back(ii(v,i)), G[v].push_back(ii(u,i));
	}
	for (int i = 1; i <= n; ++i) if ((int)G[i].size() % 2) return printf("NIE\n"), 0;

	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		path.clear(); dfs(i);
		if (path.size() > 1) euler.push_back(path);
	}
	for (int i = 0; i < (int)euler.size(); ++i) {
		vector <int> route;
		for (int j = 0; j < euler[i].size(); ++j) {
			int x = euler[i][j];
			if (!prev[x]) route.push_back(x), prev[x] = route.size();
			else {
				vector <int> cur; cur.push_back(x);
				while(route.size() > prev[x]) {
					int u = route.back(); route.pop_back(); prev[u] = 0;
					cur.push_back(u);
				}
				cur.push_back(x);
				ans.push_back(cur);
			}
		}
	}

	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); ++i) {
		printf("%d ", (int)ans[i].size() - 1);
		for (int j = 0; j < (int)ans[i].size(); ++j) printf("%d ", ans[i][j]);
		printf("\n");
	}
}