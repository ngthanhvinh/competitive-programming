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

const int INF = 1e9, N = 100010, mod = 1e5 + 3;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

ll m, n; 
int F[mod], a[N], b[N];

void process() { F[0] = 1; fo(i, 1, mod) F[i] = (1LL * F[i - 1] * i) % mod; }

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; i++) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

int C(int n, int k) { 
	if (k > n || n < 0 || k < 0) return 0;  
	int res = 1;
	res = (1LL * res * F[n]) % mod; res = (1LL * res * pw(F[k], mod - 2)) % mod; res = (1LL * res * pw(F[n - k], mod - 2)) % mod;
	return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	process();
	int T; cin >> T;
	while(T--) {
		cin >> m >> n;
		ll A = m - n + 1; int cnt = 0;
		while(A) {
			a[++cnt] = A % mod; A /= mod;
		}
		int Cnt = 0; ll B = n;
		while(B) {
			b[++Cnt] = B % mod; B /= mod; 
		}
		while(cnt < Cnt) a[++cnt] = 0;
		while(Cnt < cnt) b[++Cnt] = 0;
		//ff(i, 1, cnt) cout << a[i] << ' '; cout << "\n";
		//ff(i, 1, cnt) cout << b[i] << ' '; cout << "\n";
		int res = 1;
		ff(i, 1, cnt) res = (1LL * res * C(a[i], b[i])) % mod;
		printf("%d\n", res); 
	}
}