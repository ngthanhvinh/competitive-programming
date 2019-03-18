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

int n;
ll f[5][N];

int G(ll x) {
	int cur = 0;
	while(1) {
		cur++;
		ff(i, 1, 4) {
			if (x <= f[i][cur]) return i % 4;
			else x -= f[i][cur];
		} 
	}
}

void solve() {
	cin >> n; ll Xor = 0;
	ff(i, 1, n) { ll x; cin >> x; Xor ^= G(x); }
	if (Xor > 0) cout << "Henry\n";
	else cout << "Derek\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	ll lim = (ll)1e18 / 12;
	f[1][1] = 1; f[2][1] = 2; f[3][1] = 2; f[4][1] = 6;
	int x = 1;
	while(1) {
		x++; bool ok = 1;
		ff(i, 1, 4) {
			if (f[i][x-1] <= lim) f[i][x] = f[i][x-1] * 12;
			else { ok = 0; break; }
			//cout << i << ' ' << x << ' ' << f[i][x] << endl;
		}
		if (!ok) break;	
	}
	

	int t; cin >> t;
	while(t--) {
		solve();
	}
}