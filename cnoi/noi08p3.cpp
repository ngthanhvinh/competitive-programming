// http://wcipeg.com/problem/noi08p3
// Day 1, Problem 3 - Hiring Employees

#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int inf = 1e9;

int s, t; // source, sink
struct MaxFlowMinCost {
	struct edge {
		int u; int v; int c; int f; int w;
	};
	vector<int> G[N];
	vector<edge> e;

	void add(int u, int v, int c, int w) {
		G[u].push_back(e.size()); e.push_back({u, v, c, 0, w});
		G[v].push_back(e.size()); e.push_back({v, u, 0, 0, -w});
	}

	int inQueue[N], par[N], hd[N];
	long long d[N];

	bool ford_bellman() {
		for (int i = 1; i < N; ++i) inQueue[i] = 0, d[i] = 1e18, par[i] = -1;
		inQueue[s] = 1; d[s] = 0; par[s] = 0;
		queue<int> q; q.push(s);

		while(!q.empty()) {
			int u = q.front(); q.pop(); inQueue[u] = 0;
			for (int id : G[u]) if (e[id].c > e[id].f && d[e[id].v] > d[u] + e[id].w) {
				d[e[id].v] = d[u] + e[id].w; 
				par[e[id].v] = u;
				hd[e[id].v] = id;
				if (!inQueue[e[id].v]) q.push(e[id].v), inQueue[e[id].v] = 1;
			}
		}

		return par[t] != -1;
	}

	long long mxm() {
		int delta = inf;
		long long ret = 0;
		for (int i = t; i != s; i = par[i]) {
			int id = hd[i]; delta = min(delta, e[id].c - e[id].f); 
		}	
		for (int i = t; i != s; i = par[i]) {
			int id = hd[i]; e[id].f += delta; e[id ^ 1].f -= delta; ret += 1LL * delta * e[id].w;
		}
		return ret;
	}

	long long mincost() {
		long long ret = 0;
		while(ford_bellman()) {
			ret += mxm();
		}
		return ret;
	}
} mfmc;

int n, m, a[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	s = N - 1, t = N - 2;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n + 1; ++i) {
		if (a[i] - a[i - 1] < 0) mfmc.add(s, i, a[i - 1] - a[i], 0);
		else mfmc.add(i, t, a[i] - a[i - 1], 0);
	}

	for (int i = 1; i <= n; ++i) {
		mfmc.add(i, i + 1, inf, 0);
	}

	while(m--) {
		int l, r, c; cin >> l >> r >> c;
		mfmc.add(r + 1, l, inf, c);
	}

	cout << mfmc.mincost() << endl;
}