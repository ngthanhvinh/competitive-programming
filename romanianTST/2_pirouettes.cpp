#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int md = 1e9 + 7;

int t, n, K;
int dp[N][N][N]; // dp[time][pos][used]
int sum[N][N][N];
int c[N][N];
int ans;

void add(int &x, int y) {
	x += y; while(x >= md) x -= md; if (x < 0) x += md;
}

void make_sum(int ntime) {
	for (int used = 0; used <= K; ++used) {
		sum[ntime][0][used] = dp[ntime][0][used];
		for (int pos = 1; pos <= n; ++pos) {
			sum[ntime][pos][used] = sum[ntime][pos - 1][used] + dp[ntime][pos][used];
			sum[ntime][pos][used] -= ((sum[ntime][pos][used] >= md) ? md : 0);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> t >> n >> K;
	t /= 2;

	// prepare
	for (int i = 0; i < N; ++i) c[i][0] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= i; ++j) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % md;
	}

	dp[0][0][0] = 1; make_sum(0);
	for (int ntime = 1; ntime <= t; ++ntime) {
		for (int pos = 1; pos <= ntime && pos <= n; ++pos) {
			for (int used = 1; used <= K; ++used) {
				dp[ntime][pos][used] = sum[ntime - pos][pos - 1][used - 1];
				//printf("ntime = %d pos = %d used = %d -> dp = %d\n", ntime, pos, used, dp[ntime][pos][used]);
			}
		}
		make_sum(ntime);
	}

	// solve
	for (int nl = 0; nl <= n; ++nl) {
		for (int nr = 0; nr <= n; ++nr) {
			for (int kl = 0; kl * (kl + 1) / 2 <= t; ++kl) {
				for (int kr = 0; kl * (kl + 1) / 2 + kr * (kr + 1) / 2 <= t; ++kr) {
					if (kl + kr > K) continue;
					for (int dif = 0; dif < 2; ++dif) { // dif = 0 or dif = 1
						int hl = max(0, kr - dif - kl);
						int hr = max(0, kl - (kr - dif));

						for (int tl = 0; tl <= t; ++tl) {
							int tr = t - tl - (hl + hr) * (n + 1);
							if (tr < 0) continue;
							int reml = (hl == 0) ? n - nl : 0;
							int remr = (hr == 0) ? n - nr : 0;

							if (!dp[tl][nl][kl] || !dp[tr][nr][kr]) continue;

							int mul = 1LL * dp[tl][nl][kl] * dp[tr][nr][kr] % md;
							add(ans, 1LL * mul * c[reml + remr][K - kl - kr] % md);
						}
					}
				}
			}
		}
	}

	cout << ans << endl;
}