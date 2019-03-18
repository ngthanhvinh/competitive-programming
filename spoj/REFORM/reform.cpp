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

const int INF = 1e9, N = 1000010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, num[N], low[N], Time, par[N], cnt[N]; 
vector <vi> G;
vector <ii> edge;
int nComponent, Bridges, nChild[N], vis[N], pTree[N];

int find(int p) { return par[p] == p ? p : par[p] = find(par[p]); }
void join(int p, int q) { int x = find(p), y = find(q); cnt[y] += cnt[x]; cnt[x] = 0; par[x] = y; }

void dfs(int u, int p) {
	num[u] = low[u] = ++Time;
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (v == p) continue;
		if (num[v]) low[u] = min(low[u], num[v]);
		else {
			dfs(v, u); low[u] = min(low[u], low[v]);
			if (low[v] >= num[v]) { Bridges++; edge.pb(ii(u, v)); }
			else {
				if (find(u) != find(v)) join(u, v);
			}  
		}
	}
}

void dfsTree(int u) {
	vis[u] = 1;
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (!vis[v]) { dfsTree(v); nChild[u] += nChild[v]; pTree[v] = u; }
	}
	nChild[u] += cnt[u];
}	

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m; G.assign(n + 1, vi());
	ff(i, 1, n) par[i] = i, cnt[i] = 1;
	fo(i, 0, m) {
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	ff(i, 1, n) if (!num[i]) { nComponent++; dfs(i, i); }
	if (nComponent >= 3) return printf("0\n"), 0;

	ll ans = 0;
	G.assign(n + 1, vi()); 
	fo(i, 0, edge.size()) G[find(edge[i].fi)].pb(find(edge[i].se)), G[find(edge[i].se)].pb(find(edge[i].fi)); 
	ff(i, 1, n) if (!G[i].empty() && !vis[i]) { dfsTree(i); break; }

	if (nComponent == 2) {
		int u = find(1);
		ll tmp = (1LL * nChild[u] * (n - nChild[u]));
		ans += (1LL * (m - Bridges) * tmp);
	}
	
	if (nComponent == 1) {	
		ll tmp = (1LL * n * (n - 1) / 2 - m);
		ans += tmp * (m - Bridges);
		fo(i, 0, edge.size()) {
			int u = edge[i].fi, v = edge[i].se;
			int x = find(u), y = find(v);
			if (y == pTree[x]) swap(x, y);
			ll res = (1LL * nChild[y] * (n - nChild[y])) - 1;
			ans += res;
		}
	}
	
	printf("%lld\n", ans);
}