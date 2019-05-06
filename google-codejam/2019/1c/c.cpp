#include <bits/stdc++.h>
using namespace std;

const int N = 17;

int n, m;
char a[N][N];
int f[N][N][N][N];

int dp(int li, int lj, int ri, int rj) {
	if (li > ri || lj > rj) return 0;
	if (f[li][lj][ri][rj] != -1) {
		return f[li][lj][ri][rj];
	}

	int &ret = f[li][lj][ri][rj];

	bitset <100> bs;

	// H
	for (int i = li; i <= ri; ++i) {
		bool can = true;
		for (int j = lj; j <= rj; ++j) {
			if (a[i][j] == '#') can = false;
		}
		if (can) {
			bs[dp(li, lj, i - 1, rj) ^ dp(i + 1, lj, ri, rj)] = true;
		}
	}

	// V
	for (int j = lj; j <= rj; ++j) {
		bool can = true;
		for (int i = li; i <= ri; ++i) {
			if (a[i][j] == '#') can = false;
		}
		if (can) {
			bs[dp(li, lj, ri, j - 1) ^ dp(li, j + 1, ri, rj)] = true;
		}
	}

	//
	ret = 0;
	while(bs[ret]) ++ret;

	//cerr << li << ' ' << lj << ' ' << ri << ' ' << rj << ' ' << ret << endl;
	return ret;
}

int trace() {
	int ret = 0;

	// H
	for (int i = 1; i <= n; ++i) {
		bool can = true;
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == '#') can = false;
		}
		if (can) {
			ret += m * ((dp(1, 1, i - 1, m) ^ dp(i + 1, 1, n, m)) == 0);
		}
	}

	// V
	for (int j = 1; j <= m; ++j) {
		bool can = true;
		for (int i = 1; i <= n; ++i) {
			if (a[i][j] == '#') can = false;
		}
		if (can) {
			ret += n * ((dp(1, 1, n, j - 1) ^ dp(1, j + 1, n, m)) == 0);
		}
	}

	return ret;
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}

	memset(f, -1, sizeof f);
	dp(1, 1, n, m);

	cout << trace() << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		solve();
	}
}