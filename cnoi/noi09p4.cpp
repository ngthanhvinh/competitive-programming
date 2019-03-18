// http://wcipeg.com/problem/noi09p4
// Day 2, Problem 1 - Plants vs. Zombies

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

const int MAX = 25 * 35;

int n, m, P[MAX];
vector<int> G[MAX];
int low[MAX], num[MAX], TIME;
stack<int> st;
bool in[MAX]; // in SCC
int ans;

int id(int i, int j) { return i * m + j + 1; }

void dfs(int u) {
	num[u] = low[u] = ++TIME; st.push(u);
	for (int v : G[u]) {
		if (num[v]) low[u] = min(low[u], num[v]);
		else {
			dfs(v); low[u] = min(low[u], low[v]);
		}
	}

	if (num[u] == low[u]) {
		int v = 0;
		vector<int> scc;
		do {
			v = st.top(); st.pop(); low[v] = num[v] = inf; scc.push_back(v);
		} while(v != u);
		if (scc.size() > 1) {
			for (int v : scc) in[v] = true;
		}
	}
}

void find() {
	queue <int> q;
	for (int i = 1; i <= n * m; ++i) if (in[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : G[u]) {
			if (in[v]) continue;
			in[v] = true; q.push(v);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int c = id(i, j);
			cin >> P[c];
			int k; cin >> k;
			while(k--) {
				int x, y; cin >> x >> y; G[c].push_back(id(x, y));
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = m - 1; j >= 1; --j) G[id(i, j)].push_back(id(i, j - 1));
	}

	for (int i = 1; i <= n * m; ++i) if (!num[i]) dfs(i);
	find();

	// build flow
	int s = n * m + 1, t = n * m + 2;
	mf = Dinic(n * m + 2, s, t);
	for (int i = 1; i <= n * m; ++i) if (!in[i]) {
		if (P[i] >= 0) mf.add(i, t, P[i]), ans += P[i];
		else mf.add(s, i, -P[i]);
		for (int j : G[i]) if (!in[j]) mf.add(i, j, inf); 
	}

	cout << ans - mf.maxflow() << endl;
}