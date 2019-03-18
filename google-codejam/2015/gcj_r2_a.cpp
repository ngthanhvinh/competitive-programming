#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n, m;
char a[N][N];
int r[N], c[N];
int nc;

const int dx[] =  {-1, 1, 0, 0};
const int dy[] =  {0, 0, -1, 1};
const char ch[] = {'^', 'v', '<', '>'};

bool dfs(int x, int y, int dir) {
	int nx = x + dx[dir], ny = y + dy[dir];
	if (nx < 1 || nx > n || ny < 1 || ny > m) return 1;
	if (a[nx][ny] != '.') return 0;
	return dfs(nx, ny, dir);
}

int solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) r[i] = 0;
	for (int j = 1; j <= m; ++j) c[j] = 0;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		cin >> a[i][j];
		if (a[i][j] != '.') ++r[i], ++c[j];
	}
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) 
		if (a[i][j] != '.' && r[i] == 1 && c[j] == 1) return -1;

	int res = 0;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		for (int k = 0; k < 4; ++k) if (a[i][j] == ch[k]) {
			res += dfs(i, j, k);
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: ", i);
		int ans = solve();
		if (ans == -1) printf("IMPOSSIBLE\n");
		else printf("%d\n", ans);
	}
}