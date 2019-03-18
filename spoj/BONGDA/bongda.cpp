#include <bits/stdc++.h>
using namespace std;
const int N = 35, INF = 1e9;
typedef pair<int,int> ii;
typedef pair<int, ii> Match;
typedef vector <int> vi;

struct MaxFlow {
	int n, src, snk;
	struct edge {
		int c; int f; int u; int v;
		edge(int u, int v, int c, int f): u (u), v (v), c (c), f (f) {}
	};	
	vector <vi> G;
	vector <edge> e;
	MaxFlow(int n=0, int src=0, int snk=0): n (n), src (src), snk (snk) { e.clear(); G.assign(n + 1, vi()); }
	void addEdge(int u, int v, int c) {
		//cout << u << ' ' << v << ' ' << c << endl;
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

int n, tot, s, t;
int a[N][N];
int score[N], ans[N];
vector <Match> M;

int main() {
	scanf("%d", &n); tot = n;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) { 
		scanf("%d", &a[i][j]); 
		if (i < j && a[i][j] == 2) { 
			++tot; 
			M.push_back(Match(tot, ii(i,j)));
		}
		if (a[i][j] == 1) score[i]++;
	}
	s = ++tot; t = ++tot;

	for (int winner = 1; winner <= n; winner++) {
		int cur = score[winner];
		for (int i = 1; i <= n; i++) if (a[winner][i] == 2) ++cur;
		bool ok = 0;
		for (int i = 1; i <= n; i++) if (cur < score[i]) { ok = 1; break; }
		if (ok) continue;

		mf = MaxFlow(tot, s, t);
		
		int nMatches = 0;
		for (int i = 0; i < M.size(); i++) if (M[i].second.first != winner && M[i].second.second != winner)
			mf.addEdge(M[i].second.first, M[i].first, 1), mf.addEdge(M[i].second.second, M[i].first, 1), mf.addEdge(M[i].first, t, 1), nMatches++;

		for (int i = 1; i <= n; i++) if (i != winner) mf.addEdge(s, i, cur-score[i]);
		int res = mf.maxFlow();
		if (res == nMatches) ans[winner] = 1; else ans[winner] = 0;
	}
	
	for (int i = 1; i <= n; i++) printf("%d", ans[i]); printf("\n");
}