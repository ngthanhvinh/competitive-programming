#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

struct MaxFlow {
	int n, src, snk, m;
	static const int maxn = 1010;
	static const int INF = 1000000010;
	struct edge {
		int c; int f; int u; int v;
		edge(int u, int v, int c, int f): u (u), v (v), c (c), f (f) {}
	};	
	vector <vi> G;
	vector <edge> e;
	MaxFlow(int n=0, int src=0, int snk=0): n (n), src (src), snk (snk) { e.clear(); G.assign(n + 1, vi()); }
	void addEdge(int u, int v, int c) {
		G[u].push_back(e.size()); e.push_back(edge(u, v, c, 0)); 
		G[v].push_back(e.size()); e.push_back(edge(v, u, 0, 0)); 
	}
	vector <int> d, head;
	bool bfs() {
		d.assign(n + 1, 0); head.assign(n + 1, 0); d[src] = INF;
		queue <int> q; q.push(src); 
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for (int id: G[u]) if (!d[e[id].v] && e[id].c > e[id].f) head[e[id].v] = id, d[e[id].v] = u, q.push(e[id].v);
		}
		return (d[snk] != 0);
	}
	void mxm() {
		int delta = INF, v = 0;
		for (int u = snk; u != src; u = d[u]) {
			int id = head[u];
			delta = min(delta, e[id].c - e[id].f);
		}
		for (int u = snk; u != src; u = d[u]) {
			int id = head[u];
			e[id].f += delta; e[id^1].f -= delta;
		}
	}
	long long maxFlow() {
		long long r = 0;
		while(bfs()) mxm();
		for (int id: G[src]) r += e[id].f;
		return r;
	}
} mf;

int N, M, S, T;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M >> S >> T;
	mf = MaxFlow(N, S, T);
	while(M--) {
		int u, v, c; cin >> u >> v >> c;
		mf.addEdge(u, v, c); 
	}
	cout << mf.maxFlow() << endl;
}