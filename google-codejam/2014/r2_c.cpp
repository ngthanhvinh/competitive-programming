#include <bits/stdc++.h>
using namespace std;

const int MAX = 1005;
int W, H, B;

struct rec {
	int x0; int y0; int x1; int y1;
	bool operator < (const rec &other) const {
		return x0 < other.x0 || (x0 == other.x0 && x1 < other.x1);
	}
	bool operator > (const rec &other) const {
		return y0 < other.y0 || (y0 == other.y0 && y1 < other.y1);
	}
} a[MAX];

vector <int> Z;
int e[MAX][MAX];
int d[MAX];

typedef pair<int,int> ii;

void getDist() {
	for (int i = 1; i <= B; ++i) for (int j = 1; j <= B; ++j) if (i != j) {
		ii pi = ii(a[i].x0, a[i].x1), pj = ii(a[j].x0, a[j].x1);
		if (pi > pj) swap(pi, pj);
		int ans = 0;
		if (pi.second < pj.first) ans = max(ans, pj.first - pi.second);

		pi = ii(a[i].y0, a[i].y1), pj = ii(a[j].y0, a[j].y1);
		if (pi > pj) swap(pi, pj);
		if (pi.second < pj.first) ans = max(ans, pj.first - pi.second);

		e[i][j] = ans - 1;
	}
}

const int inf = 1e9;
typedef pair<int,int> ii;

void dijkstra() {
	for (int i = 1; i <= B; ++i) d[i] = inf;
	priority_queue < ii, vector<ii>, greater<ii> > q; q.push(ii(0, B - 1)); d[B - 1] = 0;
	while(!q.empty()) {
		int u = q.top().second, du = q.top().first; q.pop();
		if (du != d[u]) continue;
		for (int v = 1; v <= B; ++v) {
			if (d[v] > du + e[u][v]) {
				d[v] = du + e[u][v];
				q.push(ii(d[v], v));
			}
		}
	}
}

int solve() {
	cin >> W >> H >> B;
	for (int i = 1; i <= B; ++i) {
		cin >> a[i].x0 >> a[i].y0 >> a[i].x1 >> a[i].y1;
	}
	++B; a[B].x0 = -1, a[B].x1 = -1, a[B].y0 = 0, a[B].y1 = H;
	++B; a[B].x0 = W, a[B].x1 = W, a[B].y0 = 0, a[B].y1 = H;
	getDist();

	dijkstra();

	return d[B];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: %d\n", i, solve());
	}
}