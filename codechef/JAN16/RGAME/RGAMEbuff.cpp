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

ll n, a[N], f[N], sum;

int dfs(int i, int res, vi cur) {
	if (i == n) sum = (sum + res) % mod;
	int x = a[i + 1];
	vi t = cur; 
	int res1 = (res + 1LL * a[i + 1] * cur.back()) % mod; t.pb(a[i + 1]); dfs(i + 1, res1, t);
	t.clear(); t.pb(a[i + 1]); fo(j, 0, cur.size()) t.pb(cur[j]);
	res1 = (res + 1LL * a[i + 1] * *cur.begin()) % mod; dfs(i + 1, res1, t);
}

int main() {
	ios_base::sync_with_stdio(false);
	int test; cin >> test;
	while(test--) {
		cin >> n; ff(i, 0, n) cin >> a[i];
		sum = 0; vi Start = vi(1, a[0]);
		dfs(0, 0, Start);
	}
}
