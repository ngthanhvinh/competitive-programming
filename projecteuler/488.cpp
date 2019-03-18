#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 67, mod = 1e9;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

long long n;
int f[N][2][2][2][2], dp[N][2][2][2][2];

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; i++) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; n++;
	//cout<< "Correct Answer: " << ans << "\n";
	fo(i, 0, N) ff(a, 0, 1) ff(b, 0, 1) ff(c, 0, 1) ff(d, 0, 1) f[i][a][b][c][d] = -1;
	f[64][0][0][0][0] = 0;
	dp[64][0][0][0][0] = 1;
	fod(i, 64, 1) ff(a, 0, 1) ff(b, 0, 1) ff(c, 0, 1) ff(d, 0, 1) {
		// f[i][a][b][c][d] = f[i][a>1][b>a][c>b][n>c]
		if (f[i][a][b][c][d] == -1) continue;
		//cout << "current " << i << ' ' << a << ' ' << b << ' ' << c << ' ' << d << endl;
		//cout << "f " << f[i][a][b][c][d] << "\n";
		ff(bitA, 0, 1) ff(bitB, 0, 1) {
			int bitC = (bitA ^ bitB);
			////cout<< bitA << ' ' << bitB << ' ' << bitC << "\n";
			bool A = a, B = b, C = c, D = d;
			if (!A) {
				if (i == 1) continue;
				if (i != 1 && bitA) A = 1;
			} 
			if (!B) {
				if (bitA > bitB) continue;
				if (bitB > bitA) B = 1;
			}
			if (!C) {
				if (bitB > bitC) continue;
				if (bitC > bitB) C = 1;
			}
			if (!D) {
				int bitN = ((n >> (i-1)) & 1);
				if (bitC > bitN) continue;
				if (bitN > bitC) D = 1;
			}
			int cnt = 0; 
			cnt = bitA + bitB + bitC;
			int tmp = pw(2, i-1);
			cnt = (1LL * cnt * tmp) % mod;
			//cout << "buff " << i - 1 << ' ' << A << ' ' << B << ' ' << C << ' ' << D << " with " << bitA << ' ' << bitB << ' ' << bitC << " bitN = " << ((n >> (i-1)) & 1) << " and " << cnt << "\n";
			if (f[i-1][A][B][C][D] == -1) f[i-1][A][B][C][D] = 0;
			int t = (1LL * cnt * dp[i][a][b][c][d]) % mod;
			f[i-1][A][B][C][D] = (f[i-1][A][B][C][D] + f[i][a][b][c][d]) % mod;
			f[i-1][A][B][C][D] = (f[i-1][A][B][C][D] + t) % mod;
			dp[i-1][A][B][C][D] = (dp[i-1][A][B][C][D] + dp[i][a][b][c][d]) % mod;
		}
	}
	int tmp = ((-3LL * dp[0][1][1][1][1]) % mod + mod) % mod;
	cout<< (f[0][1][1][1][1] + tmp) % mod << "\n";
} 