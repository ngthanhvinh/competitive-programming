#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int M = 2005;

int n, m;
int fr[M], to[M], check[M];
int pa[N], pe[N], dep[N];
vector< pair<int,int> > G[N];
int val[M];
int in[N], out[N];

void dfs(int u) {
	for (auto e : G[u]) {
		int v = e.second, id = e.first;
		if (pa[v]) continue;
		pa[v] = u;
		pe[v] = id;
		dep[v] = dep[u] + 1;
		check[id] = true;
		dfs(v);
	}
}
void reset() {
	for (int i = 1; i <= n; ++i) G[i].clear(), pa[i] = 0, pe[i] = -1, in[i] = out[i] = 0;
	for (int i = 0; i < m; ++i) val[i] = 0, check[i] = false;
}

void solve() {
	cin >> n >> m;
	reset();
	for (int i = 0; i < m; ++i) {
		cin >> fr[i] >> to[i];
		G[fr[i]].push_back(make_pair(i, to[i]));
		G[to[i]].push_back(make_pair(i, fr[i]));
	}

	for (int i = 1; i <= n; ++i) if (!pa[i]) {
		pa[i] = i; dep[i] = 0;
		dfs(i);
	}

	for (int i = 0; i < m; ++i) if (!check[i]) {
		int u = fr[i], v = to[i];
		if (dep[u] > dep[v]) swap(u, v);
		if (v == fr[i] && u == to[i]) ++val[i]; else --val[i];
		while(v != u) {
			++val[pe[v]]; v = pa[v];
		}
	}

	for (int i = 0; i < m; ++i) if (check[i] && pa[fr[i]] == to[i]) val[i] = -val[i];

	for (int i = 0; i < m; ++i) if (val[i] == 0) { cout << "IMPOSSIBLE\n"; return; }
	for (int i = 0; i < m; ++i) cout << val[i] << ' '; cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}