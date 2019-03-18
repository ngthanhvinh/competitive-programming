#include <bits/stdc++.h>
using namespace std;
const int N = 1001, mod = 1234567890;
long long n;
long long cnt[64];
long long a[64];
long long f[4][64];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	long long cur = 1LL, x = 0;
	while(cur <= n) {
		cnt[x] = n / cur;
		x++; cur *= 2;
	}

	for (int i = 0; i < log2(n); i++) {
		a[i] = cnt[i] - cnt[i+1];
		a[i] %= mod;
	}
	
	f[0][0] = 1;
	for (int i = 1; i <= 3; i++) for (int j = 0; j < 64; j++) {
		for (int k = 0; k < 64; k++) {
			long long tmp = (1ull * f[i-1][k] * a[j ^ k]) % mod;
			f[i][j] = (f[i][j] + tmp) % mod;
		}
		//cout << i << ' ' << j << ' ' << f[i][j] << endl;
	}
	int ans = 0;
	for (int i = 1; i < 64; i++) ans = (ans + f[3][i]) % mod;
	cout << ans << endl;
}