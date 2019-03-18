#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 7;

struct Dinic {
	int n; int s; int t;
	struct edge {
		int u; int v; int c; int f;
		edge(int u=0, int v=0, int c=0, int f=0): u(u), v(v), c(c), f(f) {}
	};
	vector<edge> e;
	vector< vector<int> > G;
	Dinic(int n=0, int s=0, int t=0): n(n), s(s), t(t) { G.assign(n + 1, vector<int>()); }
	void add(int u, int v, int c) {
		G[u].push_back(e.size()); e.push_back(edge(u, v, c, 0));
		G[v].push_back(e.size()); e.push_back(edge(v, u, 0, 0));
	}

	vector<int> d, hd, ptr;
	bool bfs() {
		d.assign(n + 1, -1); hd.assign(n + 1, -1); ptr.assign(n + 1, 0); queue<int> q;
		d[s] = 0; q.push(s);
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for (int id : G[u]) if (e[id].c > e[id].f && d[e[id].v] == -1) {
				d[e[id].v] = d[u] + 1; hd[e[id].v] = id; q.push(e[id].v);
			}
		}
		return d[t] != -1;
	}
	int dfs(int u, int fl) {
		if (u == t || !fl) return fl;
		for (int &i = ptr[u]; i < (int)G[u].size(); ++i) {
			int id = G[u][i];
			if (d[e[id].v] != d[u] + 1 || e[id].f >= e[id].c) continue;
			int nxt = dfs(e[id].v, min(fl, e[id].c - e[id].f));
			if (nxt) {
				e[id].f += nxt; e[id ^ 1].f -= nxt;
				return nxt;
			}
		}
		return 0;
	}
	int maxFlow() { 
		int res = 0;
		while(bfs()) while(dfs(s, inf)); 
		for (int id : G[s]) res += e[id].f;
		return res;
	}
} mf;

const int N = 205;
int n;
string s;
map <string, int> mp;
vector <int> G[6010];
int nWords;

int solve() {
	cin >> n; nWords = 0;
	mp.clear(); cin.ignore();
	for (int i = 1; i <= n; ++i) {
		getline(cin, s); s += ' '; string tmp = "";
		for (int j = 0; j < (int)s.size(); ++j) {
			if (s[j] == ' ') {
				if (!mp.count(tmp)) mp[tmp] = ++nWords;
				G[mp[tmp]].push_back(i); tmp = "";
			} else tmp += s[j];
		}	
	}
	int tot = n;
	tot = n + nWords * 2;
	int s = 1, t = 2;
	mf = Dinic(tot, s, t);
	for (int i = 1; i <= nWords; ++i) {
		mf.add(n + 2 * i - 1, n + 2 * i, 1);
		for (int u : G[i]) {
			mf.add(u, n + 2 * i - 1, inf);
			mf.add(n + 2 * i, u, inf);
		}
	}

	for (int i = 1; i <= nWords; ++i) G[i].clear();
	return mf.maxFlow();
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		printf("Case #%d: %d\n", it, solve());
	}
}