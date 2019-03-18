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

const int INF = 1e9, N = 100010, mod = 1e9 + 7;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

ll n, a[N], f[N], sum;

int main() {
	//freopen("RGAME.in", "r", stdin);
	ios_base::sync_with_stdio(false);
	int test; cin >> test;
	while(test--) {
		cin >> n; ff(i, 0, n) cin >> a[i];
		memset(f, 0, sizeof f);
		sum = a[0]; ll t = 1;
		ff(i, 1, n) {
			f[i] = (f[i - 1] + sum * a[i]) % mod;
			f[i] = (2 * f[i]) % mod;
			if (i != 1) t = (2 * t) % mod;
			sum = (sum + t * a[i]) % mod; 
		}
		printf("%lld\n", f[n]);
	}
}