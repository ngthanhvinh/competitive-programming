#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
typedef vector<int> vi;

int res[220][220];

struct MincostFlow {
	int n, src, snk;
	struct edge {
		int c; int f; int u; int v; int w;
		edge(int u=0, int v=0, int c=0, int f=0, int w=0): u (u), v (v), c (c), f (f), w (w) {}
	};	
	vector <vi> G;
	vector <edge> e;
	MincostFlow(int n=0, int src=0, int snk=0): n (n), src (src), snk (snk) { e.clear(); G.assign(n + 1, vi()); }
	void add(int u, int v, int c, int w) {
		G[u].push_back(e.size()); res[u][v] = e.size(); e.push_back(edge(u, v, c, 0, w)); 
		G[v].push_back(e.size()); e.push_back(edge(v, u, 0, 0, -w)); 
	}
	vector <int> d, head, par;
	vector <bool> inQueue;
	bool mnm(int &a, int b) { if (a > b) a = b; else return 0; return 1; }
	bool ford_bellman() {
		queue <int> q; q.push(src); 
		d.assign(n + 1, INF); par.assign(n + 1, 0); head.assign(n + 1, 0); inQueue.assign(n + 1, 0);
		d[src] = 0; inQueue[src] = 1;
		while(!q.empty()) {
			int u = q.front(); q.pop(); inQueue[u] = 0;
			for (int id: G[u]) if (e[id].c > e[id].f && mnm(d[e[id].v], d[u] + e[id].w)) {
				if (!inQueue[e[id].v]) inQueue[e[id].v] = 1, q.push(e[id].v); 
				par[e[id].v] = u; head[e[id].v] = id;
			} 
		}
		return d[snk] != INF;
	}
	int ans;
	void mxm() {
		int delta = INF;
		for (int u = snk; u != src; u = par[u]) { int id = head[u]; delta = min(delta, e[id].c - e[id].f); }
		for (int u = snk; u != src; u = par[u]) { int id = head[u]; e[id].f += delta; e[id^1].f -= delta; ans += delta * e[id].w; }
	}
	int MinCost() { ans = 0; while(ford_bellman()) mxm(); return ans; }
} mcf;

const int N = 110;
int n, m, s, t;
char a[N][N];
int in[N+N], out[N+N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	s = n + m + 1, t = n + m + 2; mcf = MincostFlow(n + m + 2, s, t);
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		cin >> a[i][j];
		if (a[i][j] == 'G') mcf.add(i, j+n, 1, 1), out[i]++, in[j+n]++;
		else if (a[i][j] == 'T') mcf.add(j+n, i, 1, 1), in[i]++, out[j+n]++;
	}
	for (int i = 1; i <= n+m; ++i) if (in[i] > out[i]) mcf.add(i, t, in[i] - out[i], 0); else if (in[i] < out[i]) mcf.add(s, i, out[i] - in[i], 0);
	printf("%d\n", mcf.MinCost());
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == '.') putchar('.');
			else {
				if (a[i][j] == 'G') {
					if ((mcf.e[res[i][j+n]]).f == 1) putchar('.'); else putchar('G');
				}
				else {
					if ((mcf.e[res[j+n][i]]).f == 1) putchar('.'); else putchar('T');
				}
			}
		}
		putchar('\n');
	}
}