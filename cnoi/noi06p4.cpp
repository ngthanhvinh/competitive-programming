// http://wcipeg.com/problem/noi06p4
// Day 2, Problem 1 - Maximum Profit

#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

struct Dinic {
	struct edge {
		int u; int v; int c; int f;
	};
	
	int n, s, t;
	vector< vector<int> > G;
	vector<edge> e;

	Dinic(int n=0, int s=0, int t=0): n(n), s(s), t(t) {
		G.assign(n + 1, vector<int>());
		e.clear();
	}

	void add(int u, int v, int c) {
		G[u].push_back(e.size()); e.push_back({u, v, c, 0});
		G[v].push_back(e.size()); e.push_back({v, u, 0, 0});
	}

	vector<int> d, ptr;
	bool bfs() {
		ptr.assign(n + 1, 0); d.assign(n + 1, -1);
		queue <int> q;
		q.push(s); d[s] = 0;

		while(!q.empty()) {
			int u = q.front(); q.pop();
			for (int id : G[u]) if (d[e[id].v] == -1 && e[id].c > e[id].f) {
				d[e[id].v] = d[u] + 1;
				q.push(e[id].v);
			}
		}

		return d[t] != -1;
	}

	int dfs(int u, int fl) {
		if (u == t || !fl) return fl;
		for (int &i = ptr[u]; i < G[u].size(); ++i) {
			int id = G[u][i];
			if (e[id].c > e[id].f && d[e[id].v] == d[u] + 1) {
				int nxt = dfs(e[id].v, min(fl, e[id].c - e[id].f));
				if (nxt) {
					e[id].f += nxt; e[id ^ 1].f -= nxt;
					return nxt;
				}
			}
		}
		return 0;
	}

	int maxflow() {
		int ret = 0;
		while(bfs()) {
			while(int cur = dfs(s, inf)) ret += cur;
		}
		return ret;
	}	
} mf;

int n, m;
int ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	int s = n + m + 1, t = n + m + 2;
	mf = Dinic(n + m + 2, s, t);
	for (int i = 1; i <= n; ++i) {
		int P; cin >> P;
		mf.add(s, i, P);
	}
	for (int i = 1; i <= m; ++i) {
		int A, B, C; cin >> A >> B >> C;
		ans += C;
		mf.add(A, i + n, inf);
		mf.add(B, i + n, inf);
		mf.add(i + n, t, C);
	}	

	ans -= mf.maxflow(); // mincut

	cout << ans << endl;
}