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

const int INF = 1e9, N = 50, mod = (int)1e9 + 7;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int fib[N], cnt[N];
int m, n, k, q;
int f[N][11][11];

void solve() {
	cin >> n >> k; memset(cnt, 0, sizeof cnt); int mx = 0;
	fod(i, m, 0) if (n >= fib[i]) mx = max(mx, i), n -= fib[i], cnt[i]++;
	f[mx][1][0] = 1;
	fod(i, mx, 0) {
		
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	fib[0] = 1; fib[1] = 2; m = 1;
	while(fib[m] <= 1e9) { ++m; fib[m] = fib[m-1] + fib[m-2]; }

}