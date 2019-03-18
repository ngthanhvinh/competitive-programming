// D-small
#include <bits/stdc++.h>
using namespace std;

const int N = 220;
const int mod = 1e9 + 7;
const long long INF = 1e18;
const int dx[] = {0, 0, -1, +1}, dy[] = {-1, +1, 0, 0};

int n, r, c, d;
int dis[N][N];
long long mn[N][N], mx[N][N];

void bfs(int sx, int sy, int val) {
	queue < pair<int,int> > q;
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			dis[i][j] = -1;
		}
	}
	q.push(make_pair(sx, sy));
	dis[sx][sy] = 0;

	while(!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		mn[x][y] = max(mn[x][y], -1LL * dis[x][y] * d + val);
		mx[x][y] = min(mx[x][y], 1LL * dis[x][y] * d + val);

		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx < 1 || nx > r || ny < 1 || ny > c) continue;
			if (dis[nx][ny] != -1) continue;
			dis[nx][ny] = dis[x][y] + 1;
			q.push(make_pair(nx, ny));
		}
	}
}

void solve() {
	cin >> r >> c >> n >> d;
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) mn[i][j] = -INF, mx[i][j] = INF;
	}
	while(n--) {
		int x, y, val; cin >> x >> y >> val;
		bfs(x, y, val);
	}

	int res = 0;
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			if (mn[i][j] > mx[i][j]) {
				printf("IMPOSSIBLE\n"); return;
			}
			res = (res + mx[i][j]) % mod;
		}
	}

	printf("%d\n", res);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}