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

int n, m, cnt; 
vii cond;
vi a;

void process() {
	bool check = 1; vi pos(n + 1, 0);
	fo(i, 0, a.size()) pos[a[i]] = i;
	fo(i, 0, cond.size()) {
		int u = cond[i].fi, v = cond[i].se;
		if (pos[u] == pos[v] - 1) { check = 0; break; } 
	}
	if (check) cnt = (cnt + 1) % mod;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("ans.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	int test; cin >> test;
	while(test--) {
		cin >> n >> m; cond.clear(); a.clear(); cnt = 0;
		while(m--) {
			int u, v; cin >> u >> v; cond.pb(ii(u, v)); cond.pb(ii(v, u));
		}
		
		ff(i, 1, n) a.pb(i);
		do {
			process();
		} while(next_permutation(a.begin(), a.end()));
		cout << cnt << "\n";
	}
}