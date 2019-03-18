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

const int INF = 1e9, N = 2010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, p, q;
ll a[N];
int f[N][N];
int next[N], next2w[N];

bool ok(ll x) {	
	ff(i, 0, n) {
		ff(j, i, n) if (a[j] <= a[i] + x) next[i] = j;
		ff(j, i, n) if (a[j] <= a[i] + 2 * x) next2w[i] = j;
	}
	ff(i, 0, n) cout << i << ' ' << next[i] << ' ' << next2w[i] << endl;
	f[0][0] = 0;
	ff(i, 0, p) ff(j, 0, q) {
		f[i][j+1] = max(f[i][j+1], next2w[f[i][j]]);
		f[i+1][j] = max(f[i+1][j], next[f[i][j]]);
	} 
	return (f[p][q] == n);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n >> p >> q; ff(i, 1, n) cin >> a[i]; sort(a + 1, a + n + 1);
	if (p + q >= n) return cout << 1 << endl, 0;
	ll l = 1, r = 1e9;
	/*
	while(l != r) {
		ll mid = ((l + r) >> 1);
		if (ok(mid)) r = mid;
		else l = mid + 1;
	}
	*/
	cout << ok(4) << endl;
	cout << l << endl;
}