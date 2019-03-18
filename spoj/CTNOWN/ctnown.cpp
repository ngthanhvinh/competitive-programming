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

const int INF = 1e9, N = 400;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, p[N]; 
int m; ll f[N][N];

bool prime(int p) {
	if (p <= 1) return 0; if (p == 2) return 1;
	for (int i = 2; i * i <= p; i++) {
		if (p % i == 0) return 0;
	}
	return 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) {
		cin >> n; m = 0;
		ff(i, 1, n) if (prime(i)) p[++m] = i;
		ff(i, 0, n) ff(j, 0, m) f[i][j] = 0;
		ff(i, 0, n) f[i][0] = 1;
		ff(j, 1, m) ff(i, 0, n) { 
			f[i][j] = max(f[i][j - 1], f[i][j]);
			int P = p[j], t = 1;
			while(t <= i) {
				f[i][j] = max(f[i][j], f[i - t][j - 1] * t); 
				t *= P; 
				if (t > i) break;
			}
		}
		printf("%lld\n", f[n][m]);
	}
}