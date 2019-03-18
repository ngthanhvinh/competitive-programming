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

int n, m;
ii t[N];
int a[N], pos[N], s[N];
ll f[N];

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; ff(i, 1, n) cin >> a[i], s[i] = s[i-1] + a[i];
	cin >> m; ff(i, 1, m) cin >> t[i].fi >> t[i].se;
	sort(t + 1, t + m + 1);
	
	int cur = 0;
	ff(i, 1, n) {
		if (cur < m && t[cur+1].fi <= i) ++cur;
		pos[i] = cur;
		f[i] = -INFL;
	}

	ff(i, 0, t[1].fi-1) f[i] = 0;
	ff(i, t[1].fi, n) {
		if (pos[i] == pos[i-1]) f[i] = f[i-1];
		int p = pos[i];
		if (i - t[p].se < t[p].fi && i - t[p].se >= t[p-1].fi) f[i] = max(f[i], f[i - t[p].se] + s[i] - s[i - t[p].se]);
	}
	cout << f[n] << endl;
}