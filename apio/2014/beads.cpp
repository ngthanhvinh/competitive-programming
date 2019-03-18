#include <bits/stdc++.h>
using namespace std;
 
const int N = 200010;
const int inf = 1e9;
 
int n;
int f[N][2], g[N][2];
vector < pair<int,int> > G[N], ch[N];
int ans;
 
void dfs(int u, int p) {
	for (auto edge: G[u]) if (edge.second != p) {
		dfs(edge.second, u);
		ch[u].push_back(edge);
	}
	f[u][1] = -inf;
	f[u][0] = 0;
	for (auto edge: ch[u]) {
		f[u][0] += max(f[edge.second][0], f[edge.second][1] + edge.first);
	}
	for (auto edge: ch[u]) {
		int mx = f[u][0];
		mx -= max(f[edge.second][0], f[edge.second][1] + edge.first);
		mx += (f[edge.second][0] + edge.first);
		f[u][1] = max(f[u][1], mx);
	}
}
 
void re_dfs(int u, int p) {
	ans = max(ans, g[u][0] + f[u][0]);
	//cerr << "redfs " << u << ' ' << f[u][0] + g[u][0] << ' ' << f[u][1] + g[u][1] << endl;
 
	// prepare
	vector <int> L(ch[u].size() + 2, 0); L[0] = -inf;
	vector <int> R(ch[u].size() + 2, 0); R[(int)ch[u].size()] = -inf;
 
	for (int i = 0; i < (int)ch[u].size(); ++i) {
		pair<int,int> edge = ch[u][i];
		L[i + 1] = max(L[i], f[u][0] - max(f[edge.second][0], f[edge.second][1] + edge.first) + (f[edge.second][0] + edge.first));
	}
	for (int i = (int)ch[u].size() - 1; i >= 0; --i) {
		pair<int,int> edge = ch[u][i];
		R[i] = max(R[i + 1], f[u][0] - max(f[edge.second][0], f[edge.second][1] + edge.first) + (f[edge.second][0] + edge.first));
	}
 
	// solve
	for (int i = 0; i < (int)ch[u].size(); ++i) {
		int v = ch[u][i].second, w = ch[u][i].first;
		int cost = max(f[v][0], f[v][1] + w);
		int fu0 = f[u][0] - cost;
		int mx = max(L[i], R[i + 1]);
		int fu1 = mx >= 0 ? mx - cost : -inf;
		
		g[v][0] = 0, g[v][1] = -inf;
		// g[v][0]
		g[v][0] = max(g[v][0], fu0 + g[u][0]);
		g[v][0] = max(g[v][0], fu1 + g[u][0] + w);
		g[v][0] = max(g[v][0], fu0 + g[u][1] + w);
 
		// g[v][1]
		g[v][1] = max(g[v][1], g[u][0] + fu0 + w);
 
		re_dfs(v, u);
	}
}
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v, w; cin >> u >> v >> w;
		G[u].push_back(make_pair(w,v)); G[v].push_back(make_pair(w,u));
	}
 
	dfs(1,1);
	g[1][1] = -inf;
	re_dfs(1,1);
 
	cout << ans << endl;
}