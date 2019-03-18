#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int dx[] = {+1, -1, 0, 0}, dy[] = {0, 0, -1, +1};

int n, m, q, cnt;
char a[N][N];
int id[N][N], sum[N][N];
pair<int,int> where[N * N];

#define y0 ___y0
#define y1 ___y1

int x0, y0, x1, y1;
bool seen[N * N];
vector<int> vec;

void bfs(int sx, int sy) {
	where[++cnt] = make_pair(sx, sy);
	queue< pair<int,int> > q;
	id[sx][sy] = cnt;
	q.push(make_pair(sx, sy));
	while(!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx < 1 || nx > n || ny < 1 || ny > m || id[nx][ny] || a[nx][ny] != a[x][y]) continue;
			id[nx][ny] = cnt;
			q.push(make_pair(nx, ny));
		}
	}
}

int get() {
	return sum[x1][y1] - sum[x0 - 1][y1] - sum[x1][y0 - 1] + sum[x0 - 1][y0 - 1];
}

bool inside(pair<int,int> &cur) {
	int ncomp = id[cur.first][cur.second];
	if (seen[ncomp]) return true;
	bool flag = cur.first >= x0 && cur.first <= x1 && cur.second >= y0 && cur.second <= y1;
	if (!flag) {
		seen[ncomp] = true;
		vec.push_back(ncomp);
	}
	return flag;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> a[i][j];
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) if (!id[i][j]) bfs(i, j), sum[i][j]++;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	}

	// process queries
	cin >> q;
	while(q--) {
		cin >> x0 >> y0 >> x1 >> y1;
		int ans = get();
		for (int x = x0; x <= x1; ++x) {
			if (!inside(where[id[x][y0]])) ++ans;
			if (!inside(where[id[x][y1]])) ++ans;
		}
		for (int y = y0; y <= y1; ++y) {
			if (!inside(where[id[x0][y]])) ++ans;
			if (!inside(where[id[x1][y]])) ++ans;
		}
		// reset
		while(!vec.empty()) seen[vec.back()] = false, vec.pop_back();
		printf("%d\n", ans);
	}
}