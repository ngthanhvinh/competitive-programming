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

const int INF = 1e9, N = 10010, S = 110;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, cocktail[N], m, q, par[N][20];
int d[N], cnt, f[N][S<<2];
vector <vi> G, V;
vi large, small;
bool vis[N];
int isLarge[N];

void dfs(int u) {
	fo(i, 0, G[u].size()) {
		int v = G[u][i]; if (v == par[u][0]) continue;
		d[v] = d[u] + 1; par[v][0] = u; dfs(v);
	}
}

int lca(int u, int v) {
	if (d[u] < d[v]) swap(u, v);
	fod(i, 19, 0) if (d[par[u][i]] >= d[v]) u = par[u][i];
	fod(i, 19, 0) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
	return u == v ? u : par[u][0];
} 

void bfs(int type) {
	queue <int> q; memset(vis, 0, sizeof vis);
	int c = large[type-1];
	//cout << c << endl;
	//ff(i, 1, n) f[i][type] = INF;
	fo(i, 0, V[c].size()) q.push(V[c][i]), vis[V[c][i]] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		fo(i, 0, G[u].size()) {
			int v = G[u][i]; if (vis[v]) continue;
			f[v][type] = f[u][type] + 1; 
			vis[v] = 1; q.push(v);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; G.assign(n + 1, vi());
	ff(i, 1, n-1) {
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	cin >> m; V.assign(m + 1, vi());
	ff(i, 1, n) cin >> cocktail[i], V[cocktail[i]].pb(i);
	//bfs(1);
	
	ff(i, 1, m) {
		if (V[i].size() >= S) large.pb(i), isLarge[i] = ++cnt, bfs(cnt);
		else small.pb(i);
	}
	par[1][0] = 1; dfs(1);
	ff(i, 1, 19) ff(j, 1, n) par[j][i] = par[par[j][i-1]][i-1];
	
	cin >> q;
	while(q--) {
		int x, y; cin >> x >> y;
		if (isLarge[y]) {
			//cout << "Large\n";
			printf("%d\n", f[x][isLarge[y]]);
		}
		else {
			int res = INF;
			fo(i, 0, V[y].size()) {
				int k = lca(x, V[y][i]);
				//cout << k << ' ' << V[y][i] << endl;
				res = min(res, d[x] + d[V[y][i]] - 2 * d[k]);
			}
			printf("%d\n", res);
		}
	}
}