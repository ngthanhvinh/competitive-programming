#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

int n, m, r, t, k;

struct MaxFlow { // a maxflow with several sources
	struct edge {
		int u; int v; int c; int f;
		edge(int u=0, int v=0, int c=0, int f=0) : u(u), v(v), c(c), f(f) {}
	};

	int N; int t;
	MaxFlow(int N=0, int t=0): N(N), t(t) { G.assign(N + 1, vector<int>()); }

	vector< vector<int> > G;
	vector<edge> e;
	void add(int u, int v) {
		G[u].push_back(e.size()); e.push_back(edge(u, v, 1, 0));
		G[v].push_back(e.size()); e.push_back(edge(v, u, 0, 0));
	}

	vector<int> pa, pe;
	bool bfs(int s) {
		pa.assign(N + 1, -1); pe.assign(N + 1, -1);
		queue<int> q; q.push(s); pa[s] = 0;

		while(!q.empty()) {
			int u = q.front(); q.pop();
			for (int id : G[u]) if (e[id].c > e[id].f && pa[e[id].v] == -1) {
				pa[e[id].v] = u;
				pe[e[id].v] = id;
				q.push(e[id].v);
			}
		}

		return pa[t] != -1;
	}

	// solve
	vector< vector<int> > ans;
	vector<bool> del;
	int maxFlow;
	long long minCost;

	int mnm(int s) {
		int delta = inf;
		for (int i = t; i != s; i = pa[i]) {
			int id = pe[i]; delta = min(delta, e[id].c - e[id].f);
		}
		for (int i = t; i != s; i = pa[i]) {
			int id = pe[i]; e[id].f += delta; e[id^1].f -= delta;
		}
		return delta;
	}
	void run(int flow_lim) {
		maxFlow = 0;
		minCost = 0;
		del.assign(n + 1, 0);
		ans.assign(n + 1, vector<int>());
		for (int TIME = 0; TIME < flow_lim; ++TIME) {
			for (int i = 1; i <= n; ++i) {
				if (del[i]) continue;
				if (bfs(i)) {
					int delta = mnm(i);
					maxFlow += delta;
					minCost += 1LL * delta * (TIME + 1);
				} else del[i] = true;
			}
		}

		// trace
		for (int i = 1; i <= n; ++i) {
			for (int id : G[i]) {
				if (e[id].c == e[id].f) {
					ans[i].push_back(e[id].v - n);
				}
			}
		}

		// print the answers
		printf("%d %lld\n", maxFlow, 1LL * minCost * r);
		for (int i = 1; i <= n; ++i) {
			int TIME = 0;
			for (int u : ans[i]) {
				printf("%d %d %d\n", i, u, TIME);
				TIME += r;
			}
		}
	}
} mf;

int main() {
	scanf("%d %d %d %d %d", &n, &m, &r, &t, &k);
	mf = MaxFlow(n + m + 1, n + m + 1);

	while(k--) {
		int u, v; scanf("%d %d", &u, &v);
		mf.add(u, v + n);
	}
	for (int i = 1; i <= m; ++i) mf.add(i + n, n + m + 1);

	mf.run(t / r);
}