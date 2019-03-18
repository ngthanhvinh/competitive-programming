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

int n, m, P[N][20], l[N], root;
vector <vi> G;
vector <bool> vis;

void bfs() {
	queue <int> q; q.push(1); vis[1] = 1; l[1] = 1; P[1][0] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop(); 
		fo(i, 0, G[u].size()) {
			int v = G[u][i];
			if (!vis[v]) { q.push(v); vis[v] = 1; l[v] = l[u] + 1; P[v][0] = u; }
		}
	}
}

void prep() { ff(j, 1, 19) ff(i, 1, n) P[i][j] = P[P[i][j - 1]][j - 1];  }

int lca(int u, int v) {
	if (l[u] < l[v]) swap(u, v);
	fod(i, 19, 0) if (l[P[u][i]] >= l[v]) u = P[u][i];
	fod(i, 19, 0) if (P[u][i] != P[v][i]) u = P[u][i], v = P[v][i];
	return u == v ? u : P[u][0];
}

void solve() {
	G.assign(n + 1, vi()); vis.assign(n + 1, 0);
	ff(i, 1, n - 1) {
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	root = 1; bfs(); prep();
	cin >> m;
	while(m--) {
		char type; cin >> type;
		if (type == '!') { int r; cin >> r; root = r; }
		else {
			int u, v; cin >> u >> v;
			int x = lca(u, v), ans; 
			if (lca(root, u) == x) ans = lca(root, v);
			else if (lca(root, v) == x) ans = lca(root, u);
			else ans = x;
			printf("%d\n", ans);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	while(cin >> n && n) solve();
}