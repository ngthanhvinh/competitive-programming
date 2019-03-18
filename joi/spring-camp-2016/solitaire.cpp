#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int mod = 1e9 + 7;

int n;
char a[3][N];
int fact[N * 3], inv[N * 3];
int dp[N][N * 3][2];
int sum[2][N * 3];
int ans = 1;
int d, c;

int binpow(int a, int b) {
	int ret = 1;
	while(b) {
		if (b & 1) ret = 1LL * ret * a % mod; a = 1LL * a * a % mod;
		b >>= 1;
	}
	return ret;
}

int C(int n, int k) {
	if (k > n || n < 0 || k < 0) return 0;
	return 1LL * fact[n] * (1LL * inv[k] * inv[n - k] % mod) % mod;
}

int candy(int k, int n) {
	return C(n + k - 1, k - 1);
}

void add(int &x, int y) {
	x += y; while(x >= mod) x -= mod; while(x < 0) x += mod;
}

int calc(int s, int e) {
	// s: first column, e: last column
	d = 0; // the number of blank cells up to (i-1)-th column
	c = 0; // the number of blank cells in the i-th column

	sum[0][0] = 1;
	sum[1][0] = 0;

	for (int i = s; i <= e; ++i) {
		c = (a[0][i] == 'x') + (a[1][i] == 'x') + (a[2][i] == 'x');
		int cur;
		// vertically
		for (int j = 1; j <= d + c; ++j) {
			cur = 1LL * fact[c - 1] * candy(j - c + 1, c - 1) % mod;
			cur = 1LL * cur * (sum[0][d] + sum[1][d] - sum[1][j - c]) % mod;
			add(dp[i][j][0], cur);
		}
		// horizontally
		if (i != 1 && i != n && c != 1) {
			for (int j = 1; j <= d + c; ++j) {
				if (c == 3 && j >= 2) {
					cur = fact[c - 1];
					cur = 1LL * cur * candy(j - 1, 1) % mod;
					cur = 1LL * cur * candy(d - (j - 2) + 1, 1) % mod;
					cur = 1LL * cur * sum[0][j - 2] % mod;
					add(dp[i][j][1], cur);
				}
				cur = 1LL * fact[c - 1] * candy(d - (j - 1) + 1, c - 1) % mod;
				cur = 1LL * cur * sum[0][j - 1] % mod;
				add(dp[i][j][1], cur);
			}
		}
		// make sum
		d += c;
		sum[0][0] = dp[i][0][0], sum[1][0] = dp[i][0][1];
		for (int j = 1; j <= d; ++j) {
			sum[0][j] = (sum[0][j - 1] + dp[i][j][0]) % mod;
			sum[1][j] = (sum[1][j - 1] + dp[i][j][1]) % mod;
		}
	}

	int ret = 0;
	for (int j = 1; j <= d; ++j) add(ret, dp[e][j][0]), add(ret, dp[e][j][1]);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 0; i < 3; ++i) {
		for (int j = 1; j <= n; ++j) cin >> a[i][j];
	}

	// whether the state is valid?
	for (int j = 1; j <= n; ++j) {
		if (a[0][j] != 'o' && (a[0][j - 1] != 'o' || a[0][j + 1] != 'o')) {
			return cout << 0 << endl, 0;
		}
		if (a[2][j] != 'o' && (a[2][j - 1] != 'o' || a[2][j + 1] != 'o')) {
			return cout << 0 << endl, 0;
		}
	}

	// prepare
	fact[0] = 1; for (int i = 1; i < N * 3; ++i) fact[i] = 1LL * fact[i-1] * i % mod;
	inv[0] = 1; for (int i = 1; i < N * 3; ++i) inv[i] = binpow(fact[i], mod - 2);

	int cnt = 0;
	for (int i = 1; i <= n; ) {
		int j = i;
		while(j <= n && a[1][j] != 'o') ++j;
		if (i == j) {
			int cur_cnt = (a[0][i] == 'x') + (a[2][i] == 'x');
			ans = 1LL * ans * fact[cur_cnt] % mod;
			ans = 1LL * ans * candy(cnt + 1, cur_cnt) % mod;
			cnt += cur_cnt;
			++i; continue;
		}
		ans = 1LL * ans * calc(i, j - 1) % mod;
		ans = 1LL * ans * candy(cnt + 1, d) % mod;
		cnt += d;
		i = j;
	}

	cout << ans << endl;
}