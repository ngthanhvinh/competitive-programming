#include <bits/stdc++.h>
using namespace std;

long long A, B;
int a[20], b[20];
long long dp[20][2][3][100];

long long calc(int x[]) {
	// dp[pos][ok][contains how many digits?][prv]
	memset(dp, 0, sizeof dp);
	dp[0][0][0][0] = 1;
	for (int i = 1; i <= 18; ++i) {
		for (int ok = 0; ok < 2; ++ok) {
			for (int cnt = 0; cnt < 3; ++cnt) {
				for (int prv = 0; prv < 100; ++prv) { // prv contains one or two digits
					if (!dp[i-1][ok][cnt][prv]) continue;
					int mx = 9; if (!ok) mx = x[i];
					for (int dig = 0; dig <= mx; ++dig) {
						bool palindrome = false;
						if (cnt >= 1) {
							// length of palindrome can be 2
							if (dig == prv % 10) palindrome = true;
						}
						if (cnt >= 2) {
							// length of palindrome can be 3
							int nw = prv * 10 + dig; // new number
							string s = "";
							while(s.size() < 3) s += (char)(nw % 10 + '0'), nw /= 10;
							if (s[0] == s[2]) palindrome = true;
						}
						if (palindrome) continue;
						
						// ---------------------------------------------
						int cur = (prv % 10) * 10 + dig;
						int nok = ok;
						int ncnt = cnt;
						if (dig < mx) nok = 1;
						if (cnt == 0 && dig != 0) ncnt = 1;
						else if (cnt != 0) ++ncnt, ncnt = min(ncnt, 2);
						dp[i][nok][ncnt][cur] += dp[i-1][ok][cnt][prv];
					}
				}
			}
		}
	}
	long long res = 0;
	for (int suf = 0; suf < 100; ++suf) {
		for (int cnt = 1; cnt <= 2; ++cnt)
			res += dp[18][0][cnt][suf] + dp[18][1][cnt][suf];
	}
	return res;
}

void analyze(int x[], long long X) {
	for (int i = 1; i <= 18; ++i) {
		x[i] = X % 10;
		X /= 10;
	}
	reverse(x + 1, x + 19);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> A >> B;
	if (A == 0) {
		if (B == 0) printf("1\n");
		else analyze(b, B), printf("%lld\n", calc(b) + 1);
	} else {
		--A;
		analyze(a, A);
		analyze(b, B);
		printf("%lld\n", calc(b) - calc(a));
	}
}