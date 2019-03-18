#include <bits/stdc++.h>
using namespace std;
const int N = 1010, M = 10010;
#define double long double
const double INF = 1e15;
const double EPS = 1e-3;
typedef pair<int,double> ii;
typedef vector<ii> vi;

int n, m;
vector <vi> G;
int e[N][N];
int cnt[N], inQueue[N];
double d[N];

bool solve(double k) {
	G.assign(n + 1, vi());
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (e[i][j] != 1e9) G[i].push_back(ii(j, (double)e[i][j]-k));
	queue <int> q; q.push(1); inQueue[1] = 1; d[1] = 0.0; cnt[1] = 0;
	for (int i = 2; i <= n; i++) d[i] = INF, inQueue[i] = 0, cnt[i] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop(); inQueue[u] = 0;
		if (++cnt[u] > n) return 0;
		for (ii edge: G[u]) {
			int v = edge.first; double w = edge.second;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				if (!inQueue[v]) inQueue[v] = 1, q.push(v);
			}
		}
	}
	return 1;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) e[i][j] = 1e9;
	while(m--) {
		int u, v, w; cin >> u >> v >> w;
		e[u][v] = min(e[u][v], w);
	}
	
	double l = 0.0, r = (double)1e9 + 100;
	for (int i = 1; i <= 40; i++) {
		double mid = ((l + r) / 2.0);
		if (solve(mid)) l = mid;
		else r = mid;
	}
	
	if (l <= 1e9 + 10) cout << setprecision(2) << fixed << l << endl;
	else cout << "NO TOUR" << endl;
}