#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef pair<long long, ii> II;

const int N = 5010;
const long long inf = 1e18;

struct Point {
	int x; int y;
	Point(int x=0, int y=0) : x(x), y(y) {}
} a[N];

long long sqr(int x) { return 1LL * x * x; }

long long dist(Point &p, Point &q) {
	return sqr(p.x - q.x) + sqr(p.y - q.y);
}

int r, c, n;
int par[N];
vector<II> edges;
long long d[N];
long long e[N][N];
bool vis[N];

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { p = anc(p); q = anc(q); if (p != q) par[p] = q; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> r >> c >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
	// [n + 1, n + 2]: borders

	for (int i = 1; i <= n + 1; ++i) {
		for (int j = i + 1; j <= n + 2; ++j) {
			long long cur = inf;
			if (i <= n) {
				if (j <= n) {
					cur = dist(a[i], a[j]);
				} else { 
					if (j == n + 1)	cur = sqr(a[i].y);
					if (j == n + 2) cur = sqr(c - a[i].y);
				}
			}
			e[i][j] = e[j][i] = cur;
		}
	}

	// Unoptimized Dijkstra with O(n^2) time complexity
	for (int i = 1; i <= n + 2; ++i) d[i] = inf;
	d[n + 1] = 0;
	vis[n + 1] = 1;

	while(true) {
		long long mn = inf;
		int u = 0;
		for (int i = 1; i <= n + 2; ++i) 
			if (vis[i] && d[i] < mn) mn = d[i], u = i;

		if (u == 0) break;
		if (u == n + 2) break;

		vis[u] = 0;
		for (int v = 1; v <= n + 2; ++v) {
			if (v != u && d[v] > max(d[u], e[u][v])) {
				d[v] = max(d[u], e[u][v]), vis[v] = 1;
			}
		}
	}

	cout << setprecision(6) << fixed << sqrt(d[n + 2]) / 2.0 << endl;
}