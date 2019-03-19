#include <bits/stdc++.h>
using namespace std;

int n, m, p, k, sw[1 << 13];

struct edge {
	int t; int monsters;
	edge() { t = 0; monsters = 0; }
} e[3010];

const int N = 210;
vector < pair<int,int> > G[N];

typedef pair < int, int > ii;
typedef pair < int, ii > II;
int f[N][1 << 13];

int dijkstra() {
	priority_queue < II, vector <II>, greater <II> > q;
	for (int i = 1; i <= n; ++i) for (int mask = 0; mask < (1 << p); ++mask) f[i][mask] = 1e9;
	f[1][sw[1]] = 0; q.push(II(0, ii(1, sw[1])));

	while(!q.empty()) {
		int u = q.top().second.first, mask = q.top().second.second, d = q.top().first; q.pop();
		if (d != f[u][mask]) continue;
		if (u == n) return f[u][mask];
		for (int i = 0; i < G[u].size(); ++i) {
			int v = G[u][i].second, id = G[u][i].first;
			if ((e[id].monsters & mask) == e[id].monsters && f[v][mask | sw[v]] > d + e[id].t) {
				f[v][mask | sw[v]] = d + e[id].t;
				q.push(II(f[v][mask | sw[v]], ii(v, (mask | sw[v]))));
			}
		}
	}

	return -1;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> p >> k;
	while(k--) {
		int w, q, r; cin >> w >> q;
		while(q--) {
			cin >> r; sw[w] |= (1 << r - 1);
		}
	}

	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(make_pair(i,v)); 
		G[v].push_back(make_pair(i,u));
		cin >> e[i].t;
		int w; cin >> w; while(w--) { int x; cin >> x; e[i].monsters |= (1 << x - 1); }
	}

	cout << dijkstra() << endl;
}