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

const int INF = 1e9, N = 100010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, a[N];
ll f[N], l[N], r[N];
ll ans;

void solve() {
	cin >> n; ff(i, 1, n) cin >> a[i], f[i] = f[i-1] + a[i]; r[n+1] = -INFL;
	ff(i, 1, n) l[i] = min(l[i-1], f[i]);
	fod(i, n, 1) r[i] = max(r[i+1], f[i]);
	ans = -INFL;
	ff(i, 1, n) ans = max(ans, f[i] - l[i-1]);
	//cout << ans << endl;
	ff(i, 1, n-1) ans = max(ans, r[i+1] - l[i-1] - a[i]);
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) solve();
}