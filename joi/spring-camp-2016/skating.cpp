#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef pair<int, ii> II;

const int dx[] = {0, 0, -1, +1};
const int dy[] = {-1, +1, 0, 0};
const int N = 1005;
const int inf = 2e9;

int n, m, sx, sy, ex, ey;
char a[N][N];
int d[N][N];
pair<int,int> to[N][N][4];

bool valid(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= m && a[x][y] == '.');
}

void prepare() {
	int last;

	// 0, 1
	for (int i = 1; i <= n; ++i) {
		last = 0;
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == '#') last = j + 1;
			to[i][j][0] = ii(i, last);
		}
		last = m + 1;
		for (int j = m; j >= 1; --j) {
			if (a[i][j] == '#') last = j - 1;
			to[i][j][1] = ii(i, last);
		}
	}
	
	// 2, 3
	for (int j = 1; j <= m; ++j) {
		last = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i][j] == '#') last = i + 1;
			to[i][j][2] = ii(last, j);
		}
		last = n + 1;
		for (int i = n; i >= 1; --i) {
			if (a[i][j] == '#') last = i - 1;
			to[i][j][3] = ii(last, j);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> a[i][j];
	}
	prepare();

	cin >> sx >> sy >> ex >> ey;

	// Dijkstra
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) d[i][j] = inf;
	}

	priority_queue < II, vector<II>, greater<II> > pq;
	pq.push(II(0, ii(sx, sy))); d[sx][sy] = 0;

	while(!pq.empty()) {
		II top = pq.top(); pq.pop();
		int x = top.second.first, y = top.second.second, dis = top.first;
		if (d[x][y] != dis) continue;

		for (int dir = 0; dir < 4; ++dir) {
			pair<int,int> nxt = to[x][y][dir];
			int nx = nxt.first, ny = nxt.second;
			// + 1
			if (d[nx][ny] > dis + 1) {
				d[nx][ny] = dis + 1; pq.push(II(d[nx][ny], ii(nx, ny)));
			}
			// + 2
			nx = x + dx[dir], ny = y + dy[dir];
			if (valid(nx, ny) && d[nx][ny] > dis + 2) {
				d[nx][ny] = dis + 2; pq.push(II(d[nx][ny], ii(nx, ny)));
			}
		}
	}

	printf("%d\n", d[ex][ey] == inf ? -1 : d[ex][ey]);
}