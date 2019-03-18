#include <bits/stdc++.h>
using namespace std;

const int N = 25;
const int dx[] = {0, 0, -1, +1};
const int dy[] = {-1, +1, 0, 0};

int r, c, a[N][N], b[N][N], tmp[N][N];
int t[4];

int calc() {
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			tmp[i][j] = b[i][j];
		}
	}

	int ret = 0;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			// bfs
			if (b[i][j] == 1) {
				int cur = 0;
				queue < pair<int,int> > q;
				q.push(make_pair(i, j));
				b[i][j] = 0; // visited
				while(!q.empty()) {
					int x = q.front().first;
					int y = q.front().second;
					++cur;
					q.pop();
					for (int dir = 0; dir < 4; ++dir) {
						int nx = x + dx[dir], ny = y + dy[dir];
						if (nx < 0 || nx >= r || ny < 0 || ny >= c || !b[nx][ny]) continue;
						q.push(make_pair(nx, ny));
						b[nx][ny] = 0; // visited
					}
				}
				ret = max(ret, cur);
			}
		}
	}
	return ret;
}

void solve() {
	memset(a, -1, sizeof a);
	cin >> r >> c;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			char ch; cin >> ch;
			a[i][j] = (ch == 'B');
		}
	}

	int res = 0;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			// intersection at (i, j)
			for (t[0] = 0; t[0] < 3; ++t[0]) {
				for (t[1] = 0; t[1] < 3; ++t[1]) {
					for (t[2] = 0; t[2] < 3; ++t[2]) {
						for (t[3] = 0; t[3] < 3; ++t[3]) {
							// check whether there exists a similar state
							bool have = false;
							for (int k = -1; k < r; ++k) for (int l = -1; l < c; ++l) {
								bool ok = true;
								if (t[0] != 2 && !(k >= 0 && l >= 0 && a[k][l] == t[0])) ok = false;
								if (t[1] != 2 && !(k >= 0 && l < c - 1 && a[k][l + 1] == t[1])) ok = false;
								if (t[2] != 2 && !(k < r - 1 && l >= 0 && a[k + 1][l] == t[2])) ok = false;
								if (t[3] != 2 && !(k < r - 1 && l < c - 1 && a[k + 1][l + 1] == t[3])) ok = false;
								have |= ok;
							}
							if (!have) continue;

							// 0 1
							// 2 3
							memset(b, 0, sizeof b);
							for (int k = 0; k <= i; ++k) for (int l = 0; l <= j; ++l) if (a[k][l] == t[0]) b[k][l] = 1;
							for (int k = 0; k <= i; ++k) for (int l = j + 1; l < c; ++l) if (a[k][l] == t[1]) b[k][l] = 1;
							for (int k = i + 1; k < r; ++k) for (int l = 0; l <= j; ++l) if (a[k][l] == t[2]) b[k][l] = 1;
							for (int k = i + 1; k < r; ++k) for (int l = j + 1; l < c; ++l) if (a[k][l] == t[3]) b[k][l] = 1;

							res = max(res, calc());
						}
					}
				}
			}
		}
	}

	printf("%d\n", res);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;

	for (int itest = 1; itest <= ntest; ++itest) {
		printf("Case #%d: ", itest);
		solve(); 
	}
}