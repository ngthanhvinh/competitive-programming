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

int n, m, q, a[N][N]; 
ll f[N][N], r[N][N];

void process() {
	ff(i, 1, n) ff(j, 1, m) r[i][j] = r[i][j - 1] + a[i][j];
	ff(i, 1, n) ff(j, 1, m) f[i][j] = f[i - 1][j] + r[i][j];
}

ll F(int X1, int Y1, int X2, int Y2) { return f[X2][Y2] - f[X1 - 1][Y2] - f[X2][Y1 - 1] + f[X1 - 1][Y1 - 1]; }

ll binarySearch(int X1, int Y1, int X2, int Y2) {
	int l, r; ll sum = F(X1, Y1, X2, Y2), ans = INFL; 
	l = Y1, r = Y2;
	while(l != r) {
		int mid = ((l + r + 1) >> 1);
		if (F(X1, Y1, X2, mid) > (sum >> 1)) r = mid - 1;
		else l = mid;
 	}
 	ans = min(ans, abs(sum - 2 * F(X1, Y1, X2, l))); if (l + 1 <= Y2) ans = min(ans, abs(sum - 2 * F(X1, Y1, X2, l + 1))); 
 	l = X1, r = X2;
 	while(l != r) {
		int mid = ((l + r + 1) >> 1);
		if (F(X1, Y1, mid, Y2) > (sum >> 1)) r = mid - 1;
		else l = mid;
 	}
 	ans = min(ans, abs(sum - 2 * F(X1, Y1, l, Y2))); if (l + 1 <= Y2) ans = min(ans, abs(sum - 2 * F(X1, Y1, l + 1, Y2))); 
 	return ans; 
}

int main() {
	//ios_base::sync_with_stdio(false); cin.tie(0);
	//cin >> n >> m >> q; ff(i, 1, n) ff(j, 1, m) cin >> a[i][j];
	scanf("%d%d%d", &n, &m, &q); ff(i, 1, n) ff(j, 1, m) scanf("%d", &a[i][j]);
	process();
	while(q--) {
		int x, y, u, v; //cin >> x >> y >> u >> v;
		scanf("%d%d%d%d", &x, &y, &u, &v);
		printf("%lld\n", binarySearch(x, y, u, v));
	}
}