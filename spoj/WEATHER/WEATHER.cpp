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

const int INF = 1e9, N = 110;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, num[N], low[N], Time, nChild[N]; 
vector <vi> G;
stack <int> st;
vector <bool> vis;
ll ans;

void dfs(int u, int p) {
	num[u] = low[u] = ++Time;
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (v == p) continue;
		if (num[v]) low[u] = min(low[u], num[v]);
		else {
			dfs(v, u); low[u] = min(low[u], low[v]);
			if (low[v] >= num[v]) st.push(v); 
		}
	}
}

void dfs(int u) {
	vis[u] = 1;
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (!vis[v]) { dfs(v); nChild[u] += nChild[v]; }
	}
	nChild[u]++;
}	

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n >> m; G.assign(n + 1, vi()); vis.assign(n + 1, 0);
	while(m--) {
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	ff(i, 1, n) if (!vis[i]) dfs(i); 
	ff(i, 1, n) {
		if (!num[i]) dfs(i, i);
	}
	while(!st.empty()) {
		int u = st.top(); st.pop();
		ans += 1LL * nChild[u] * (n - nChild[u]);
	}
	printf("%lld\n", ans);
}