#include <bits/stdc++.h>
using namespace std;

const int N = 155;

int n, m;
int *a[N], *sum[N];
int ans = 1e9;

void init() {
	for (int i = 0; i <= n; ++i) {
		a[i] = new int [m + 2];
		sum[i] = new int [m + 2];
	}
}

int get1(int x0, int y0, int x1, int y1) {
	return sum[x1][y1] - sum[x0 - 1][y1] - sum[x1][y0 - 1] + sum[x0 - 1][y0 - 1];
}

int get0(int x0, int y0, int x1, int y1) {
	return (x1 - x0 + 1) * (y1 - y0 + 1) - get1(x0, y0, x1, y1);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	init();

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
		}
	}

	for (int ru = 1; ru <= n; ++ru) { // up
		for (int rd = ru; rd <= n; ++rd) { // down
			int more = get1(1, 1, ru - 1, m) + get1(rd + 1, 1, n, m);
			int mn = 1e9;
			int max_pref = 0;
			for (int c = 1; c <= m; ++c) {
				int cur = get0(ru, 1, rd, c);
				mn = min(mn, cur - max_pref + get1(ru, c + 1, rd, m));
				max_pref = max(max_pref, cur - get1(ru, 1, rd, c));
				//printf("ru = %d rd = %d c = %d\n cur = %d\n -> mn = %d\n", ru, rd, c, cur, mn);
			}
			ans = min(ans, mn + more);
		}
	}

	cout << ans << endl;
}