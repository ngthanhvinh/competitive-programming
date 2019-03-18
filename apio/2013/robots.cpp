#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int INF = 1e9;
const int dx[] = {-1, 0, +1, 0};
const int dy[] = {0, +1, 0, -1};
typedef pair<int,int> ii;

int n, r, c;
char a[N][N];
int dis[N][N][10][10];
ii dest[N][N][4];

struct state { 
	int dis; int x; int y; int l; int r; 
	bool operator < (const state &other) const {
		return dis > other.dis;
	}
};

bool inside(int x, int y) { return x >= 1 && x <= r && y >= 1 && y <= c; }

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> c >> r;
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			cin >> a[i][j];
		}
	}
	
	// calculate dest[][][]
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			for (int dir = 0; dir < 4; ++dir) {
				if (dest[i][j][dir] == make_pair(0,0)) { // was not visited
					// dfs using stack
					int destx, desty;
					int x = i, y = j, curdir = dir;
					stack < pair<ii, int> > st; // ((x, y), dir)
					while(true) {
						if (dest[x][y][curdir] != make_pair(0, 0)) {
							destx = dest[x][y][curdir].first;
							desty = dest[x][y][curdir].second;
							break;
						}

						st.push(make_pair(ii(x, y), curdir));
						int ndir = curdir;
						if (a[x][y] == 'A') ndir = (curdir + 3) % 4;
						if (a[x][y] == 'C') ndir = (curdir + 1) % 4;

						int nx = x + dx[ndir], ny = y + dy[ndir];
						if (!inside(nx, ny) || a[nx][ny] == 'x') {
							destx = x; desty = y; break;
						}

						x = nx; y = ny; curdir = ndir;
					}

					while(!st.empty()) {
						x = st.top().first.first, y = st.top().first.second, curdir = st.top().second;
						st.pop();
						dest[x][y][curdir] = {destx, desty};
					}
				}
			}
		}
	}	
	
	// BFS
	priority_queue <state> pq;
	queue <state> q;
	for (int i = 1; i <= r; ++i) for (int j = 1; j <= c; ++j) {
		for (int l = 1; l <= n; ++l) for (int r = l; r <= n; ++r) {
			dis[i][j][l][r] = INF;
		}
	}
	for (int i = 1; i <= r; ++i) for (int j = 1; j <= c; ++j) {
		if (a[i][j] >= '1' && a[i][j] <= '9') {
			dis[i][j][a[i][j] - '0'][a[i][j] - '0'] = 0;
			q.push({0, i, j, a[i][j] - '0', a[i][j] - '0'});
		}
	}

	while(!q.empty() || !pq.empty()) {
		state t_pq, t_q, t; 
		if (!pq.empty()) t_pq = pq.top(); else t_pq = {INF, 0, 0, 0, 0};
		if (!q.empty()) t_q = q.front(); else t_q = {INF, 0, 0, 0, 0};

		// take the best state
		if (t_q.dis < t_pq.dis) t = t_q, q.pop();
		else t = t_pq, pq.pop();

		// solve
		int x = t.x, y = t.y, l = t.l, r = t.r;
		if (l == 1 && r == n) {
			printf("%d\n", dis[x][y][l][r]); return 0;
		}
		if (t.dis != dis[x][y][l][r]) continue;
		
		//cerr << x << ' ' << y << "[" << l << ' ' << r << "] -> " << dis[x][y][l][r] << endl;

		// push
		for (int dir = 0; dir < 4; ++dir) {
			int nx = dest[x][y][dir].first, ny = dest[x][y][dir].second;
			if (dis[nx][ny][l][r] > dis[x][y][l][r] + 1) {
				dis[nx][ny][l][r] = dis[x][y][l][r] + 1;
				q.push({dis[nx][ny][l][r], nx, ny, l, r});
			};
		}

		// merge
		for (int k = 1; k <= l - 1; ++k) if (dis[x][y][k][l - 1] <= t.dis) {
			if (dis[x][y][k][r] > dis[x][y][l][r] + dis[x][y][k][l - 1]) {
				dis[x][y][k][r] = dis[x][y][l][r] + dis[x][y][k][l - 1];
				pq.push({dis[x][y][k][r], x, y, k, r});
			}
		}
		for (int k = r + 1; k <= n; ++k) if (dis[x][y][r + 1][k] <= t.dis) {
			if (dis[x][y][l][k] > dis[x][y][l][r] + dis[x][y][r + 1][k]) {
				dis[x][y][l][k] = dis[x][y][l][r] + dis[x][y][r + 1][k];
				pq.push({dis[x][y][l][k], x, y, l, k});
			}
		}
	}
	
	printf("-1\n");
}
