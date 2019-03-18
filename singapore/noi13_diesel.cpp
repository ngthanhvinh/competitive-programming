// Wrong Answer!!
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int inf = 1e9;
const int dx[] = {-1,+1,0,0}, dy[] = {0,0,-1,+1};

typedef pair<int,int> ii;
typedef pair<int, ii> iii;

int n, m;
int a[N][N];
int d[N][N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) cin >> a[i][j];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) d[i][j] = inf;
	}
	priority_queue < iii, vector<iii>, greater<iii> > pq;
	d[0][0] = 0;
	pq.push(iii(0, ii(0, 0)));

	while(!pq.empty()) {
		iii top = pq.top(); pq.pop();
		int x = top.second.first, y = top.second.second, dist = top.first;
		if (dist != d[x][y]) continue;

		int w = 33000 - dist;

		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

			int cost = 10 + 4 * (max(0, a[nx][ny] - a[x][y]) / 100) * (w / 1000);
			if (dist + cost > 25000) continue; // run out of diesel

			if (d[nx][ny] > dist + cost) {
				d[nx][ny] = dist + cost;
				pq.push(iii(d[nx][ny], ii(nx, ny)));
			}
		}
	}

	if (d[n - 1][m - 1] == inf) printf("-1\n");
	else printf("%d\n", 25000 - d[n - 1][m - 1]);
}