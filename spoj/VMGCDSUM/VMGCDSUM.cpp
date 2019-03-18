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

int n, p[N], k[N], ans = 1; 

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; ++i) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; ff(i, 1, n) cin >> p[i] >> k[i];
	ff(i, 1, n) {
		int P = p[i], K = k[i];
		int Q = pw(P - 1, mod - 2), r = (pw(P, K) + pw(P, K + 1)) % mod; r = (r + mod - 2) % mod;
		r = (1LL * r * Q) % mod;
		//cout << r << "\n";
		ans = (1LL * ans * r) % mod;
	}
	printf("%d\n", ans);
}