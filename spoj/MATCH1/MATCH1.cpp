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

int n, m, vis[N], match[N], t = 0, cnt;
vector <vi> G;

bool dfs(int u) {
	if (vis[u] != t) vis[u] = t; else return 0;
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (!match[v] || dfs(match[v])) { match[v] = u; return 1; }
	}
	return 0;
}

int main() {
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin >> m >> n; G.assign(m + 1, vi());
	int u, v; 
	while(cin >> u >> v) {
		G[u].pb(v); 
	}
	ff(i, 1, m) {
		t++; cnt += dfs(i);
	}
	printf("%d\n", cnt);
	ff(i, 1, n) if (match[i]) printf("%d %d\n", match[i], i);
}