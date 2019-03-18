#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

typedef vector<int> vi;
struct MaxFlow {
	int n, src, snk, m;
	struct edge {
		int c; int f; int u; int v;
		edge(int u, int v, int c, int f): u (u), v (v), c (c), f (f) {}
	};	
	vector <vi> G;
	vector <edge> e;
	MaxFlow(int n=0, int src=0, int snk=0): n (n), src (src), snk (snk) { 
		e.clear(); G.assign(n + 1, vi()); 
	}

	void add(int u, int v, int c) {
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
	int mxm() {
		int delta = INF;
		for (int u = snk; u != src; u = d[u]) {
			int id = head[u];
			delta = min(delta, e[id].c - e[id].f);
		}
		for (int u = snk; u != src; u = d[u]) {
			int id = head[u];
			e[id].f += delta; e[id^1].f -= delta;
		}
		return delta;
	}
	int maxFlow() {
		int r = 0;
		while(bfs()) r += mxm();
		return r;
	}
} mf;

const int N = 105;

int n, a[N][N];
int idrow[N][N * 2];
int idcol[N][N * 2];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
			a[i][j] += n;
		}
	}

	int s = 5 * n * n + 1;
	int t = 5 * n * n + 2;
	mf = MaxFlow(5 * n * n + 2, s, t);

	// build flow
	auto decode = [&](int x, int y) {
		return (x - 1) * n + y;
	};
	int cur = n * n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= n + n; ++j) if (j != n) {
			idrow[i][j] = ++cur;
			mf.add(s, idrow[i][j], 1);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= n + n; ++j) if (j != n) {
			idcol[i][j] = ++cur;
			mf.add(idcol[i][j], t, 1);
		}
	}

	// build flow
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int val = a[i][j];
			mf.add(idrow[i][val], decode(i, j), 1);
			mf.add(decode(i, j), idcol[j][val], 1);
		}
	}

	int res = mf.maxFlow();
	printf("%d\n", n * n - res);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;

	for (int itest = 1; itest <= ntest; ++itest) {
		printf("Case #%d: ", itest);
		solve(); 
	}
}