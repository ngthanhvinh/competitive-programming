#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int L = 100005;
const long long INF = 1e18;

int n, m, t, len;
int fr[N], to[N], w[N];
int a[L];
vector < pair<int,int> > g[N];
long long dp[L][N][2];

struct state {
	long long dis; int pos; int last_edge; int which;
	bool operator < (const state &other) const {
		return dis > other.dis;
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m >> t >> len;
	assert(t == 1);

	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v >> w[i];
		fr[i] = u;
		to[i] = v;
		g[u].push_back(make_pair(i, v));
		g[v].push_back(make_pair(i, u));
	}
	for (int i = 1; i <= len; ++i) cin >> a[i];

	int p, q; cin >> p >> q; // first query
	a[p] = q;

	// Dijkstra
	priority_queue <state> pq;
	for (int i = 1; i <= len; ++i) {
		for (int j = 0; j <= m; ++j) {
			for (int k = 0; k < 2; ++k) dp[i][j][k] = INF;
		}
	}
	
	fr[0] = a[1];
	dp[1][0][0] = 0;
	pq.push({0, 1, 0, 0});

	while(!pq.empty()) {
		auto top = pq.top(); pq.pop();
		long long dis = top.dis;
		int pos = top.pos;
		int last_edge = top.last_edge;
		int which = top.which;
		if (dis != dp[pos][last_edge][which]) continue;
		if (pos == len) return printf("%lld\n", dis), 0;

		int u = which == 0 ? fr[last_edge] : to[last_edge];
		for (auto &e : g[u]) {
			int v = e.second, id = e.first;
			if (id != last_edge && dp[pos + (v == a[pos + 1])][id][v == to[id]] > dis + w[id]) {
				pq.push({dp[pos + (v == a[pos + 1])][id][v == to[id]] = dis + w[id], pos + (v == a[pos + 1]), id, v == to[id]});
			}
		}
	}

	printf("-1\n"); // invalid
}