#include <bits/stdc++.h>
using namespace std;

const int N = 500005;
const int M = 5e6 + 5;

int n, m, q;
int c[M], fr[M], to[M];
int dsu[N];
vector<int> edges;
vector< pair<int,int> > G[N];
int mn[N];

int anc(int p) { return p == dsu[p] ? p : dsu[p] = anc(dsu[p]); }
void join(int p, int q) { p = anc(p); q = anc(q); dsu[p] = q; }

int main() {
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 0; i < m; ++i) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		c[i] = w; fr[i] = u; to[i] = v;
		edges.push_back(i);
	}
	// build maximum spanning tree
	for (int i = 1; i <= n; ++i) dsu[i] = i;
	sort(edges.begin(), edges.end(), [&](int x, int y) {
		return c[x] > c[y];
	});
	for (int i = 0; i < m; ++i) {
		int w = c[edges[i]];
		int u = fr[edges[i]];
		int v = to[edges[i]];
		if (anc(u) == anc(v)) continue;
		join(u, v);
		G[u].push_back(make_pair(w, v));
		G[v].push_back(make_pair(w, u));
	}

	for (int i = 1; i <= n; ++i) mn[i] = -1;
	mn[1] = 1e9;
	// bfs
	queue <int> qu; qu.push(1);
	while(!qu.empty()) {
		int u = qu.front(); qu.pop();
		for (int i = 0; i < G[u].size(); ++i) {
			int v = G[u][i].second, w = G[u][i].first;
			if (mn[v] == -1) {
				mn[v] = min(mn[u], w); qu.push(v);
			}
		}
	}
	
	// answer queries
	while(q-- > 0) {
		int u; scanf("%d", &u);
		printf("%d\n", mn[u]);
	}
}