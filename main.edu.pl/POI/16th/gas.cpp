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

int n, s, k, res;
vector <vi> G;
ll f[N][21], g[N][21];

void dfs(int u, int p = -1) {
	fo(i, 0, G[u].size()) {
		int v = G[u][i]; if (v == p) continue;
		dfs(v, u);
		fo(i, 0, k) f[u][i+1] += f[v][i], g[u][i] += g[v][i+1];
	}
	f[u][0] = 1;
	int add = (f[u][k] + s - 1) / s;
	g[u][k] = 1ll * add * s;
	res += add;
	ff(i, 0, k) {
		ll x = min(f[u][i], g[u][i]);
		f[u][i] -= x; g[u][i] -= x;
	}
	ff(i, 0, k-1) {
		ll x = min(f[u][i], g[u][i+1]);
		f[u][i] -= x; g[u][i+1] -= x;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n >> s >> k; G.assign(n + 1, vi());
	ff(i, 1, n-1) {
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	dfs(1);
	ll x = 0;
	fod(i, k, 0) {
		x += g[1][i];
		if (x < f[1][i]) {
			int cnt = (f[1][i] - x + s - 1) / s;
			res += cnt;
			x += 1ll * cnt * s;
		}
		x -= f[1][i];
	}
	cout << res << endl;
}