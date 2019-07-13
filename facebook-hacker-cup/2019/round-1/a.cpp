#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int M = 1005;
const int INF = 1e9 + 123;

int n, m;
int d[N][N];
bool is[N][N];

struct edge {
	int u;
	int v;
	int w;
	edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
};
vector <edge> rEdges;

void reset() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			d[i][j] = (i == j) ? 0 : INF;
			is[i][j] = false;
		}
	}
	rEdges.clear();
}

void solve() {
	cin >> n >> m;
	reset();

	bool ok = true;
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		if (u == v && w > 0) {
			ok = false;
		}
		d[u][v] = d[v][u] = w;
		is[u][v] = is[v][u] = true;
	}

	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (is[i][j] && d[i][j] > d[i][k] + d[k][j]) {
					ok = false;
				}
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}

	if (!ok) {
		printf("Impossible\n");
		return;
	}

	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (is[i][j]) {
				rEdges.push_back(edge(i, j, d[i][j]));
			}
		}
	}

	printf("%d\n", (int)rEdges.size());
	for (auto &p : rEdges) {
		printf("%d %d %d\n", p.u, p.v, p.w);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		printf("Case #%d: ", it);
		solve();
	}
}