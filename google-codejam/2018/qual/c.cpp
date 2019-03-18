#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int dx[] = {0, 0, 0, -1, -1, -1, +1, +1, +1};
const int dy[] = {-1, 0, +1, -1, 0, +1, -1, 0, +1};

int mincell;
bool a[N][N];

void solve() {
	cin >> mincell;

	int n = sqrt(mincell);
	int m = 1;
	while(n * m < mincell) ++m;

	// [1 ... n] [1 ... m]
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) a[i][j] = 0;
	}

	while(true) {
		int bi = 2;
		int bj = 2;
		int best = 0;
		for (int i = 2; i <= n - 1; ++i) {
			for (int j = 2; j <= m - 1; ++j) {
				int blank = 0;
				for (int dir = 0; dir < 9; ++dir) {
					int ni = i + dx[dir], nj = j + dy[dir];
					if (ni >= 1 && ni <= n && nj >= 1 && nj <= m && !a[ni][nj]) ++blank;
				}
				if (blank > best) {
					best = blank;
					bi = i;
					bj = j;
				}
			}
		}

		// ask
		cout << bi << ' ' << bj << endl;
		int reply_x, reply_y;
		cin >> reply_x >> reply_y;

		if (reply_x == 0 && reply_y == 0) return; // OK
		a[reply_x][reply_y] = 1;
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int tt; cin >> tt;
	while(tt--) {
		solve();
	}
}