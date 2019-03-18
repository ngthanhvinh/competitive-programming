#include "factories.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n;
vector< pair<int,int> > G[N];
int t[N], TIME;
int dep[N], e[N << 1], lg[N << 1];
pair<int,int> rmq[N << 1][20];
long long dist[N];

void dfs(int u, int p) {
	t[u] = ++TIME; e[TIME] = u;
	for (auto &edge : G[u]) {
		int v = edge.second, w = edge.first; if (v == p) continue;
		dist[v] = dist[u] + w; dep[v] = dep[u] + 1; dfs(v, u);
		e[++TIME] = u;
	}
}

int get(int l, int r) {
	int k = lg[r - l + 1];
	pair<int,int> res = min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
	return res.second;
}

int lca(int u, int v) {
	if (t[u] > t[v]) swap(u, v);
	return get(t[u], t[v]);
}

void Init(int N, int A[], int B[], int D[]) {
	n = N;
	for (int i = 0; i < N - 1; ++i) {
		G[A[i]].push_back(make_pair(D[i], B[i]));
		G[B[i]].push_back(make_pair(D[i], A[i]));
	}
	dfs(0, 0);
	for (int i = 1; i <= TIME; ++i) rmq[i][0] = make_pair(dep[e[i]], e[i]);
	for (int j = 1; j <= 19; ++j) for (int i = 1; i <= TIME; ++i) {
		rmq[i][j] = min(rmq[i][j-1], rmq[i + (1 << j-1)][j-1]);
	}
	for (int i = 2; i <= TIME; ++i) lg[i] = lg[i >> 1] + 1;
}

// ------------------------------------------------------------------

const long long inf = 1e18;
vector<int> nG[N];
long long f[N][2];
bool a[N][2];
long long ans;

void solve(int u) {
	for (int i = 0; i < 2; ++i) if (a[u][i]) f[u][i] = 0;
	for (int v : nG[u]) {
		solve(v);
		for (int i = 0; i < 2; ++i) f[u][i] = min(f[u][i], f[v][i] + dist[v] - dist[u]);
	}
	ans = min(ans, f[u][0] + f[u][1]);
}

long long Query(int S, int X[], int T, int Y[]) {
	vector<int> imp;

	// build a new tree containing at most 2 * (S + T) vertices
	for (int i = 0; i < S; ++i) a[X[i]][0] = 1, imp.push_back(X[i]);
	for (int i = 0; i < T; ++i) a[Y[i]][1] = 1, imp.push_back(Y[i]);
	sort(imp.begin(), imp.end(), [&](int x, int y) { return t[x] < t[y]; });
	
	int sz = imp.size();
	for (int i = 1; i < sz; ++i) {
		imp.push_back(lca(imp[i-1], imp[i]));
	}
	sort(imp.begin(), imp.end(), [&](int x, int y) { return t[x] < t[y]; });
	imp.resize(distance(imp.begin(), unique(imp.begin(), imp.end())));

	sz = imp.size();
	for (int i = 1; i < sz; ++i) {
		int p = lca(imp[i-1], imp[i]);
		nG[p].push_back(imp[i]);
	}

	// solve
	ans = inf;
	for (int u : imp) f[u][0] = f[u][1] = inf;
	solve(imp[0]);

	// reset
	for (int i = 0; i < S; ++i) a[X[i]][0] = 0;
	for (int i = 0; i < T; ++i) a[Y[i]][1] = 0;
	for (int u : imp) nG[u].clear();

	return ans;
}
