#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int inf = 1e9;

int n, m, ncomp, root;
vector<int> g[N], ng[N];
vector<int> vec[N];
int low[N], num[N], TIME, pos[N];
int in[N];
bool vis[N];
stack<int> st;

void dfs(int u) {
	low[u] = num[u] = ++TIME; st.push(u);
	for (int i = 0; i < g[u].size(); ++i) {
		int v = g[u][i];
		if (num[v]) low[u] = min(low[u], num[v]);
		else {
			dfs(v); low[u] = min(low[u], low[v]);
		}
	}

	if (low[u] == num[u]) {
		int v = 0;
		++ncomp;
		do {
			v = st.top(); st.pop();
			vec[ncomp].push_back(v); pos[v] = ncomp;
			low[v] = num[v] = inf;
		} while(v != u);
	}
}

void redfs(int u) {
	vis[u] = true;
	for (int i = 0; i < ng[u].size(); ++i) {
		int v = ng[u][i];
		if (!vis[v]) redfs(v);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
	}

	for (int i = 1; i <= n; ++i) if (!num[i]) dfs(i);
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			int v = g[i][j]; 
			if (pos[v] == pos[i]) continue;
			ng[pos[i]].push_back(pos[v]);
			in[pos[v]]++;
		}
	}
	for (int i = 1; i <= ncomp; ++i) if (!in[i]) {
		root = i; redfs(i); break;
	}
	for (int i = 1; i <= ncomp; ++i) if (!vis[i]) return printf("0\n"), 0;

	printf("%d\n", vec[root].size());
	sort(vec[root].begin(), vec[root].end());
	for (int i = 0; i < vec[root].size(); ++i) {
		printf("%d ", vec[root][i]);
	}
	printf("\n");
}