#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int n, m;
int x[N], y[N], s[N];
vector<int> G[N], oldG[N];
int mx[N], my[N];
bool check[N];

void bfs(int x) {
	for (int i = 1; i <= n; ++i) check[i] = 0;
	queue <int> que; que.push(x); check[x] = 1;

	while(!que.empty()) {
		int u = que.front(); que.pop();
		for (int i = 0; i < oldG[u].size(); ++i) {
			int v = oldG[u][i]; 
			if (!check[v]) que.push(v), check[v] = 1;
		}
	}

	for (int i = 1; i <= n; ++i) if (i != x && check[i]) {
		G[x].push_back(i);
	}
}

bool dfs(int u) {
	if (!u) return true;
	for (int v : G[u]) {
		if (check[v]) continue;
		check[v] = 1;
		if (dfs(my[v])) { my[v] = u; mx[u] = v; return true; }
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i] >> s[i];

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) if (i != j) {
			if (y[i] < y[j] && max(abs(x[i] - x[j]), y[j] - y[i]) <= max(s[i], s[j])) {
				oldG[i].push_back(j);
			}
		}
	}

	// build edges
	for (int i = 1; i <= n; ++i) bfs(i);

	// bipartite matching
	int rem = n, prev_rem = n + 1;
	while(rem > 0 && prev_rem > rem) {
		prev_rem = rem;
		for (int i = 1; i <= n; ++i) check[i] = 0;
		for (int i = 1; i <= n; ++i) if (!mx[i]) rem -= dfs(i);
	}

	int max_matching = 0;
	for (int i = 1; i <= n; ++i) max_matching += mx[i] != 0;
	if (max_matching == 0) printf("-1\n");
	else printf("%d\n", n - max_matching + 1);
}