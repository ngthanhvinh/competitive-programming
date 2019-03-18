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

const int INF = 1e9, N = 1010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, f[N][N];
vi res;

int main() {
	// freopen("egg.txt", "r", stdin);
 //   freopen("egg.ans", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	fo(i, 0, N) fo(j, 0, N) f[i][j] = INF;
	fo(i, 1, N) f[i][1] = 1, f[i][0] = 0;
   fo(j, 1, N) f[1][j] = j;

	ff(i, 2, 100) fo(j, 2, N) {
		ff(k, 1, j) {
			f[i][j] = min(f[i][j], max(f[i - 1][k - 1], f[i][j - k]));
		}
		f[i][j]++;
	}
   res.pb(0); res.pb(1); int tmp = 1;
   ff(i, 2, 10) {
      tmp *= 2;
      ff(j, 1, tmp) res.pb(i);
   }
   
	int t; cin >> t; while(t--) {
		cin >> n >> m;
		if (n <= 100) printf("%d\n", f[n][m]);
      else printf("%d\n", res[m]);
	}
}