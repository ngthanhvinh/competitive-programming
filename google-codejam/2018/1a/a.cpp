#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int r, c, h, v;
int a[N][N];
vector < pair<int,int> > vh, vv;

int get(int x1, int y1, int x2, int y2) {
	return a[x2][y2] - a[x2][y1 - 1] - a[x1 - 1][y2] + a[x1 - 1][y1 - 1];
}

void solve() {
	cin >> r >> c >> h >> v;
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			char c; cin >> c;
			a[i][j] = c == '@';
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}

	if (a[r][c] == 0) {
		printf("POSSIBLE\n"); return;
	}

	if (a[r][c] % ((h + 1) * (v + 1)) != 0) {
		printf("IMPOSSIBLE\n");
		return;
	}

	vh.clear();
	vv.clear();

	int sh = a[r][c] / (h + 1);
	for (int i = 1; i <= r; ) {
		int j = i;
		while(j <= r && get(i, 1, j, c) <= sh) ++j; --j;
		if (get(i, 1, j, c) != sh) {
			printf("IMPOSSIBLE\n"); return;
		}
		vh.push_back(make_pair(i, j));
		i = j + 1;
	}
	if (vh.size() != h + 1) {
		printf("IMPOSSIBLE\n"); return;
	}

	int sv = a[r][c] / (v + 1);
	for (int i = 1; i <= c; ) {
		int j = i;
		while(j <= c && get(1, i, r, j) <= sv) ++j; --j;
		if (get(1, i, r, j) != sv) {
			printf("IMPOSSIBLE\n"); return;
		}
		vv.push_back(make_pair(i, j));
		i = j + 1;
	}
	if (vv.size() != v + 1) {
		printf("IMPOSSIBLE\n"); return;
	}

	int in = a[r][c] / (h + 1) / (v + 1);
	for (auto &rows : vh) {
		for (auto &cols : vv) {
			if (get(rows.first, cols.first, rows.second, cols.second) != in) {
				printf("IMPOSSIBLE\n"); return;
			}
		}
	}

	printf("POSSIBLE\n");
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}