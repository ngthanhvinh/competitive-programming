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

int n, par[N][18], l[N];
long long ans[N];
long long dist[N], last[N]; 
vector <vii> G;

void bfs() {
	queue <int> q; q.push(1); l[1] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < G[u].size(); ++i) {
			int v = G[u][i].fi; if (v == par[u][0]) continue;
			par[v][0] = u; l[v] = l[u] + 1;
			q.push(v);
		}
	}
}

long long find(int u, int s, int t) {
	fod(i, 17, 0) if (l[par[s][i]] >= l[u] && dist[par[s][i]] < t - dist[par[s][i]]) s = par[s][i];
	long long res = max(dist[s], t - dist[s]);
	res = min(res, max(dist[par[s][0]], t - dist[par[s][0]]));
	return res;
}

void dfs(int u) {
	last[u] = u; dist[u] = 0;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i].fi, w = G[u][i].se; 
		if (v == par[u][0]) continue;
		dfs(v);
		if (dist[u] < dist[v] + w) { dist[u] = dist[v] + w; last[u] = last[v]; }
	}
	long long mx = 0LL;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i].fi, w = G[u][i].se;
		if (v == par[u][0] || last[v] == last[u]) continue;
		mx = max(mx, dist[v] + w);
	}
	if (mx == dist[u]) { ans[u] = mx; return; }
	if (last[u] == u && dist[u] == 0) { ans[u] = 0; return; }
	ans[u] = find(u, last[u], dist[u] + mx);
}

void solve() {
	cin >> n; G.assign(n + 1, vii()); memset(dist, 0, sizeof dist);
	ff(i, 1, n-1) {
		int u, v, w; cin >> u >> v >> w;
		G[u].pb(ii(v, w)); G[v].pb(ii(u, w));
	}
	bfs(); for (int i = 1; i <= 17; i++) for (int j = 1; j <= n; j++) par[j][i] = par[par[j][i-1]][i-1];
	dfs(1); ff(i, 1, n) printf("%lld\n", ans[i]);
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) solve();
}