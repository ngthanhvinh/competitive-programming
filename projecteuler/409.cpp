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

const int INF = 1e9, N = 10000010, mod = 1e9 + 7;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n;
int f[N], g[N];

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
	cin >> n;
	f[1] = 0, g[1] = (pw(2, n) - 1 + mod) % mod;
	f[0] = 1, g[0] = 0;
	int tmp = (pw(2, n) - 1 + mod) % mod;
	int cur = tmp;
	ff(i, 2, n) {
		cur = (1LL * cur * ((tmp - i + 1 + mod) % mod)) % mod;
		//cout << cur << endl;
		int r = (tmp - (i - 2) + mod) % mod;
		r = (1LL * r * ((1LL * f[i-2] * (i-1)) % mod)) % mod;
		f[i] = (g[i-1] - r + mod) % mod;
		g[i] = (cur - f[i] + mod) % mod;
		//cout << i << ' ' << f[i] << ' ' << g[i] << endl;
	}	
	cout << g[n] << endl;
}