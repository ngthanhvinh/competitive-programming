#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const long long inf = 1e18;
const int dx[] = {0, 0, -1, +1}, dy[] = {-1, +1, 0, 0};

int n, H, W, A, B, C;
int endX, endY;
int d[N][N];
long long f[N][N][5];

struct State {
	long long dist; int x; int y; int dir;
	// dir == 4: the ball is currently kept by a player
	State(long long dist=0, int x=0, int y=0, int dir=0): dist(dist), x(x), y(y), dir(dir) {}
	bool operator < (const State &rhs) const {
		return dist > rhs.dist;
	}
};
priority_queue <State> pq;
queue < pair<int,int> > q;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> H >> W; // [0 -> H, 0 -> W]
	cin >> A >> B >> C;

	// PREPARE
	for (int x = 0; x <= H; ++x) {
		for (int y = 0; y <= W; ++y) {
			d[x][y] = -1; // minimum distance of (x,y) and a player
			for (int dir = 0; dir < 5; ++dir) f[x][y][dir] = inf; // for Dijkstra
		}
	}
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y; cin >> x >> y; // the position of the i-th player	
		if (i == 1) {
			pq.push(State(0, x, y, 4));
			f[x][y][4] = 0;
		} else if (i == n) {
			endX = x; endY = y;
		}
		q.push(make_pair(x,y));
		d[x][y] = 0;
	}
	while(!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx < 0 || nx > H || ny < 0 || ny > W || d[nx][ny] != -1) continue;
			d[nx][ny] = d[x][y] + 1;
			q.push(make_pair(nx,ny));
		}
	}	
	//------------------------------------------------------------------------------------

	// DIJKSTRA
	while(!pq.empty()) {
		State top = pq.top(); pq.pop();
		int x = top.x, y = top.y, dir = top.dir;
		if (f[x][y][dir] != top.dist) continue;
		if (x == endX && y == endY) return printf("%lld\n", top.dist), 0;

		int nx, ny; // next position

		if (dir == 4) {
			// kick the ball
			for (int ndir = 0; ndir < 4; ++ndir) {
				nx = x + dx[ndir], ny = y + dy[ndir];
				if (nx < 0 || nx > H || ny < 0 || ny > W) continue;
				if (f[nx][ny][ndir] > top.dist + A + B) {
					f[nx][ny][ndir] = top.dist + A + B;
					pq.push(State(f[nx][ny][ndir], nx, ny, ndir));
				}
			}
			// move the ball
			for (int ndir = 0; ndir < 4; ++ndir) {
				nx = x + dx[ndir], ny = y + dy[ndir];
				if (nx < 0 || nx > H || ny < 0 || ny > W) continue;
				if (f[nx][ny][4] > top.dist + C) {
					f[nx][ny][4] = top.dist + C;
					pq.push(State(f[nx][ny][4], nx, ny, 4));
				}
			}
		} else {
			// the ball keeps moving
			nx = x + dx[dir], ny = y + dy[dir];
			if (nx >= 0 && nx <= H && ny >= 0 && ny <= W && f[nx][ny][dir] > top.dist + A) {
				f[nx][ny][dir] = top.dist + A;
				pq.push(State(f[nx][ny][dir], nx, ny, dir));
			}
			// the ball stops and some player grabs it
			if (f[x][y][4] > top.dist + 1LL * C * d[x][y]) {
				f[x][y][4] = top.dist + 1LL * C * d[x][y];
				pq.push(State(f[x][y][4], x, y, 4));
			}
		}
	}
}