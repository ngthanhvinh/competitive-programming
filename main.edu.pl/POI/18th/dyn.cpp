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

const int INF = 1e9, N = 300010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, a[N], f[N], child[N], k[N], ans, x;
vector <vi> G;

void dfs(int u, int p = -1) {
	if (a[u]) f[u] = 0, child[u] = 1;
	k[u] = -INF;
	fo(i, 0, G[u].size()) {
		int v = G[u][i]; if (v == p) continue;
		dfs(v, u);
		if (k[v] > 0) k[u] = max(k[u], k[v] - 1);
		child[u] += child[v];
		f[u] = max(f[u], f[v] + 1);
 	}
 	if (!child[u]) { f[u] = -INF; return; }
 	if (f[u] <= k[u]) f[u] = -INF, child[u] = 0;
 	if (f[u] >= x) ans++, f[u] = -INF, k[u] = x, child[u] = 0;
}

bool check() {
	memset(child, 0, sizeof child);
	ans = 0;
	ff(i, 1, n) f[i] = -INF;
	dfs(1);

	if (f[1] >= 0) ans++;
	return (ans <= m);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n >> m; G.assign(n + 1, vi());
	ff(i, 1, n) cin >> a[i];
	ff(i, 1, n-1) {
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	
	int l = 0, r = n;
	while(l != r) {
		x = ((l + r) >> 1);
		if (check()) r = x;
		else l = x + 1;
	}
	cout << l << endl;
}