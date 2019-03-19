#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int n;
long long target;
long long a[N], b[N];
unsigned long long ans;
unsigned long long f[N][2][2];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	for (int bit = 31; bit >= 0; --bit) {
		target = 0;
		for (int i = 1; i <= n; ++i) {
			b[i] = (a[i] >> bit & 1);
			target ^= b[i];
			if (a[i] >= (1LL << bit)) a[i] -= (1LL << bit);
		}

		memset(f, 0, sizeof f);
		f[0][0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) for (int ok = 0; ok < 2; ++ok) {
				if (!f[i-1][j][ok]) continue;
				for (int nxt = 0; nxt <= b[i]; ++nxt) {
					int nj = j, nok = ok; long long mul = a[i] + 1;
					nj ^= nxt;
					if (nxt < b[i]) {
						nok = 1;
						if (ok) mul = (1LL << bit); else mul = 1;
					}
					f[i][nj][nok] += mul * f[i-1][j][ok];
				}
			}
		}
		ans += f[n][0][1];

		if (target == 1) break;
	}
	
	ans += target == 0;
	cout << ans - 1 << endl;
}