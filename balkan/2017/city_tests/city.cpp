#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
const int inf = 2e9 + 7;

int n, a[N];
long long k;
vector<int> G[N];
bool del[N];
int ch[N], d[N];
int go[N];
int dist[N];
int rmq[N][62];

void calc(int u, int p) {
	ch[u] = 1;
	for (int i = 0; i < (int)G[u].size(); ++i) {
		int v = G[u][i]; if (v == p || del[v]) continue;
		d[v] = d[u] + 1;
		calc(v, u);
		ch[u] += ch[v];
	}
}

int centroid(int u, int p, int r) {
	for (int i = 0; i < (int)G[u].size(); ++i) {
		int v = G[u][i]; if (v == p || del[v]) continue;
		if (2 * ch[v] > ch[r]) return centroid(v, u, r); 
	}
	return u;
}

int cmp(int u, int v) {
	if (a[u] - d[u] < a[v] - d[v]) swap(u, v);
	if (a[u] - d[u] == a[v] - d[v] && u > v) swap(u, v);
	return u;
}

int mn;
void dfs(int u, int p) {
	mn = cmp(mn, u);
 	for (int i = 0; i < (int)G[u].size(); ++i) {
		int v = G[u][i]; if (v == p || del[v]) continue;
		dfs(v, u);
	}
}

void upd_val(int u, int val) {
	if (dist[u] < a[val] - d[val] - d[u]) dist[u] = a[val] - d[val] - d[u], go[u] = val;
	if (dist[u] == a[val] - d[val] - d[u] && val < go[u]) go[u] = val;
}

void upd(int u, int p, int val) {
	upd_val(u, val);
	for (int i = 0; i < (int)G[u].size(); ++i) {
		int v = G[u][i]; if (v == p || del[v]) continue;
		upd(v, u, val);
	}
}

void solve(int u) {
	d[u] = 0; calc(u, u);
	int c = centroid(u, u, u); del[c] = 1;

	d[c] = 0; calc(c, c);
	
	vector< pair<int,int> > T;
	for (int i = 0; i < (int)G[c].size(); ++i) {
		int v = G[c][i]; if (v == c || del[v]) continue;
		mn = v; dfs(v, v);
		T.push_back(make_pair(v, mn));
	}

	vector<int> L((int)T.size() + 2, 0);
	vector<int> R((int)T.size() + 2, 0);
	for (int i = 1; i <= (int)T.size(); ++i) L[i] = cmp(L[i-1], T[i-1].second);
	for (int i = (int)T.size() - 1; i >= 0; --i) R[i] = cmp(R[i+1], T[i].second);

	for (int i = 0; i < (int)T.size(); ++i) {
		int u = T[i].first;
		int lef = L[i], rig = R[i + 1];
		lef = cmp(lef, rig), lef = cmp(lef, c);
		upd(u, u, lef);
	}
	upd_val(c, R[0]);

	for (int i = 0; i < (int)T.size(); ++i) {
		int u = T[i].first; solve(u);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) go[i] = inf, dist[i] = -inf;
	a[0] = -inf;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}

	solve(1);

	for (int i = 1; i <= n; ++i) rmq[i][0] = go[i];
	for (int j = 1; j < 62; ++j) for (int i = 1; i <= n; ++i) rmq[i][j] = rmq[rmq[i][j-1]][j-1];

	int ans = 1;
	for (int j = 61; j >= 0; --j) if ((1LL << j) <= k) k -= (1LL << j), ans = rmq[ans][j];
	printf("%d\n", ans);
}