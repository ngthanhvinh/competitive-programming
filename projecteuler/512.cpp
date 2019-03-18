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

const int INF = 1e9, N = 20010, mod = 1000000000;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n; 
int f[N][201];

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; int limit = 200;
	//cout << limit << endl;
	f[1][1] = 3;
	for (int i = 2; i <= n; i++) for (int j = 1; j <= limit && j <= i; j++) {
		// remain: i    pick j in this column
		if (j == 1) {
			for (int k = 1; k <= limit && k <= i-j; k++) f[i][j] = (f[i][j] + (2LL * f[i-j][k]) % mod) % mod;
		}
		else {
			for (int k = j-1; k <= limit && k <= i-j; k++) f[i][j] = (f[i][j] + f[i-j][k]) % mod;
			if (j == 2 && i-j >= 1) f[i][j] = (f[i][j] + f[i-j][1]) % mod;
		}
		//cout << i << ' ' << j << ' ' << f[i][j] << endl;
	}
	int ans = 0;
	for (int i = 0; i <= limit; i++) ans = (ans + f[n][i]) % mod;
	cout << ans << endl;
}