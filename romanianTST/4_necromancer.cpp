#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int inf = 1e9;

struct Dinic {
	struct edge {
		int u; int v; int c; int f;
		edge(int u=0, int v=0, int c=0, int f=0) : u(u), v(v), c(c), f(f) {}
	};

	int n, s, t;
	vector< vector<int> > G;
	vector<edge> e;
	Dinic(int n=0, int s=0, int t=0) : n(n), s(s), t(t) {
		G.assign(n + 1, vector<int>()); e.clear();
	}
	void add(int u, int v, int c) {
		G[u].push_back(e.size()); e.push_back(edge(u, v, c, 0));
		G[v].push_back(e.size()); e.push_back(edge(v, u, 0, 0));
	}

	vector<int> d, ptr;
	bool bfs() {
		d.assign(n + 1, -1); ptr.assign(n + 1, 0);
		queue <int> q;
		q.push(s); d[s] = 0;

		while(!q.empty()) {
			int u = q.front(); q.pop();
			for (int id : G[u]) if (e[id].c > e[id].f && d[e[id].v] == -1) {
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
			if (e[id].c <= e[id].f || d[e[id].v] != d[u] + 1) continue;
			int nxt = dfs(e[id].v, min(fl, e[id].c - e[id].f));
			if (nxt) {
				e[id].f += nxt; e[id ^ 1].f -= nxt; return nxt;
			}
		}
		return 0;
	}

	int max_flow() {
		int ret = 0;
		while(bfs()) {
			while(int cur = dfs(s, inf)) ret += cur;
		}
		return ret;
	}
} mf;

int n, k, can;
bool e[N][N];

bool check(int lim) {
	// <= lim - 1
	int src = n + k + 1, snk = n + k + 2;
	mf = Dinic(n + k + 2, src, snk);

	for (int i = 1; i <= n; ++i) if (e[1][i]) {
		for (int j = 1; j <= k; ++j) if (e[j][i] == 0) mf.add(j, i + k, 1);
	}
	for (int i = 1; i <= k; ++i) mf.add(src, i, lim - 1);
	for (int i = 1; i <= n; ++i) mf.add(i + k, snk, 1);

	return mf.max_flow() == n - can;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k; // n citizens, k people ran for office

	for (int i = 1; i <= n; ++i) {
		int sz; cin >> sz; // sz <= k
		for (int j = 0; j < sz; ++j) {
			int x; cin >> x;
			if (j > 0) {
				e[x][i] = 1; // there is no edge (x, i)
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (e[1][i] == 0) ++can;
	}
	
	int low = can, high = n;
	while(low < high) {
		int mid = ((low + high) >> 1);
		if (check(mid)) high = mid;
		else low = mid + 1;
	}

	cout << low - can << endl;
}