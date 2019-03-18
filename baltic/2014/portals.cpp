#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int inf = 1e9 + 7;

int n, m;
int sx, sy;
int cx, cy;

string a[N];
int d[N][N];
const int dx[] = {0, 1, -1, 0}; // {right, down, up, left}
const int dy[] = {1, 0, 0, -1};

int f[N][N][4];

typedef pair<int,int> ii;
typedef pair<int,ii> II;

void dijkstra() {
	priority_queue < II, vector<II>, greater<II> > q;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) d[i][j] = inf;
	d[sx][sy] = 0; q.push(II(0, ii(sx,sy)));
	while(!q.empty()) {
		II T = q.top(); q.pop();
		int x = T.second.first, y = T.second.second, dd = T.first;
		if (dd != d[x][y]) continue;
		cerr << x << ' ' << y << ' ' << dd << endl;
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == '#') continue;
			if (d[nx][ny] > dd + 1) d[nx][ny] = dd + 1, q.push(II(d[nx][ny], ii(nx, ny))), cerr << "-> " << nx << ' ' << ny << endl;
		}
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x, ny = y;
			if (dir == 0 || dir == 3) ny = f[x][y][dir] + dy[dir];
			if (dir == 1 || dir == 2) nx = f[x][y][dir] + dx[dir];
			if (d[nx][ny] > dd + 1) d[nx][ny] = dd + 1, q.push(II(d[nx][ny], ii(nx, ny))), cerr << "-> " << nx << ' ' << ny << endl;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i <= m + 1; ++i) a[0] += '#', a[n + 1] += '#';
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; a[i] = '#' + a[i]; a[i] += '#';
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == 'S') sx = i, sy = j;
			if (a[i][j] == 'C') cx = i, cy = j;
		}
	}

	for (int i = 1; i <= n; ++i) {
		f[i][0][0] = 0, f[i][m + 1][3] = m + 1;
		for (int j = 1; j <= m; ++j) f[i][j][0] = (a[i][j] != '#' ? f[i][j-1][0] : j); // right
		for (int j = m; j >= 1; --j) f[i][j][3] = (a[i][j] != '#' ? f[i][j+1][3] : j); // left
	}

	for (int j = 1; j <= m; ++j) {
		f[0][j][1] = 0, f[n + 1][j][2] = n + 1;
		for (int i = 1; i <= n; ++i) f[i][j][1] = (a[i][j] != '#' ? f[i-1][j][1] : i); // down
		for (int i = n; i >= 1; --i) f[i][j][2] = (a[i][j] != '#' ? f[i+1][j][2] : i); // up
	}

	dijkstra();
	cout << d[cx][cy] << endl;
}