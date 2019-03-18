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

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1ll << i) <= b; i++) {
		if (b & (1ll << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
 	}
 	return res;
}
int F[N], f[N];
void prep() { F[0] = 1; fo(i, 1, N) F[i] = (1LL * F[i - 1] * i) % mod; }

int n, x, a[N]; ll m;

void solve() {
	cin >> n >> x >> m; ff(i, 1, n) { ll v; cin >> v; a[i] = v % mod; }
	//cout << n << ' ' << x << ' ' << m << "\n";
	//ff(i, 1, n) cout << a[i] << ' '; cout << "\n";
	int res = 0;
	f[1] = 1; ff(i, 2, x) f[i] = (1LL * f[i - 1] * ((i + m - 2)%mod)) % mod;
	ff(i, 1, x) f[i] = (1LL * f[i] * pw(F[i - 1], mod - 2)) % mod;
	ff(i, 1, x) res = (res + ((1LL * f[i] * a[x + 1 - i]) % mod)) % mod;
	printf("%d\n", res);
	
}

int main() {
	//freopen("stropr.in", "r", stdin);
	//freopen("stropr.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	prep();
	int t; cin >> t;
	while(t--) {
		solve();
	}
}