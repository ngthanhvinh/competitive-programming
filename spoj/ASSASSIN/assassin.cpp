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

const int INF = 1e9, N = 1010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, low[N], num[N], Time, cnt, pos[N], t, vis[N], match[N];
int ans, Case;
bool edge[N][N], check[N];
vector <vi> G, canGo;
stack <int> s;

void dfs(int u) {
	num[u] = low[u] = ++Time; s.push(u);
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (num[v]) low[u] = min(low[u], num[v]);
		else { dfs(v); low[u] = min(low[u], low[v]); }
	}
	if (low[u] == num[u]) {
		cnt++; int v; 
		do {
			v = s.top(); s.pop();
			low[v] = num[v] = INF; pos[v] = cnt;
		} while(v != u);
	}
}

void init() {
	cin >> n >> m; G.assign(n + 1, vi()); 
	memset(edge, 0, sizeof edge); memset(vis, 0, sizeof vis); 
	memset(match, 0, sizeof match); memset(check, 0, sizeof check); 
	memset(low, 0, sizeof low); memset(num, 0, sizeof num);
	cnt = 0; Time = 0; t = 0; ans = 0; s = stack<int>();
	while(m--) {
		int u, v; cin >> u >> v;
		G[u].pb(v); edge[u][v] = 1;
	}
}

void process() {
	ff(i, 1, n) if (!num[i]) dfs(i); // Strong Components 
	G.assign(cnt + 1, vi()); // compress each Strong Component to a vertex of a DAG
	ff(i, 1, n) ff(j, 1, n) if (pos[i] != pos[j] && edge[i][j]) {
		G[pos[i]].pb(pos[j]);
	}	
}

bool visit(int u) {
	if (vis[u] != t) vis[u] = t; else return 0;
	fo(i, 0, canGo[u].size()) {
		int v = canGo[u][i];
		if (!match[v] || visit(match[v])) { match[v] = u; return 1; }
	}
	return 0;
}

void operator += (vi &a, vi b) { fo(i, 0, b.size()) a.pb(b[i]); }

void dfs_pos(int u) {
	check[u] = 1;
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (!check[v]) dfs_pos(v);
		canGo[u].pb(v); canGo[u] += canGo[v];
	}
	//cout << "dfs: " << u << "\n";
	//fo(i, 0, canGo[u].size()) cout << canGo[u][i] << " "; cout << "\n";
}

void solve() {
	canGo.assign(cnt + 1, vi());
	ff(i, 1, cnt) {
		dfs_pos(i);
	}
	ff(i, 1, cnt) { t++; ans += visit(i); }
	ans = cnt - ans;
	printf("Case %d: %d\n", ++Case, ans);
}

int main() {
	ios_base::sync_with_stdio(false);
	int T; cin >> T;
	while(T--) {
		init();
		process();
		solve();
	}
}