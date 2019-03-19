#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int M = 250005;

int n, m, t, newEdges;
int route[M];
map <int,int> mp[N];
vector< pair<int,int> > G[N];
int fr[M], to[M], del[M], prv[M], nxt[M];
vector<int> vec[N];
int in[N], out[N];
vector<int> E, ans;

void invalid() { printf("NIE\n"); exit(0); }

void init() {
	cin >> t;
	while(t--) {
		int k; cin >> k;
		for (int i = 0; i < k; ++i) cin >> route[i];
		vector<int> edges;
		for (int i = 0; i < k - 1; ++i) {
			// every edge of the route must exist
			if (!mp[route[i]].count(route[i + 1])) invalid();
			edges.push_back(mp[route[i]][route[i + 1]]);
		}
		for (int i = 0; i < (int)edges.size() - 1; ++i) {
			// prv and nxt must be unique
			int new_nxt = edges[i + 1], new_prv = edges[i];
			if (nxt[edges[i]] && nxt[edges[i]] != new_nxt) invalid();
			if (prv[edges[i+1]] && prv[edges[i+1]] != new_prv) invalid();
			nxt[edges[i]] = new_nxt;
			prv[edges[i+1]] = new_prv;
		}
	}
}

void compress() { // compress the sequences	
	for (int i = 1; i <= m; ++i) { // unrelevant edges
		if (!prv[i] && !nxt[i]) {
			G[fr[i]].push_back(make_pair(i, to[i]));
			del[i] = true;
		}
	}
	newEdges = 0;
	for (int i = 1; i <= m; ++i) if (!del[i] && !prv[i]) { // uncyclic paths
		int cur = i;
		++newEdges;
		while(true) {
			vec[newEdges].push_back(cur);
			del[cur] = true;
			if (!nxt[cur]) break;
			cur = nxt[cur];
		}
		G[fr[i]].push_back(make_pair(m + newEdges, to[cur]));
	}
	for (int i = 1; i <= m; ++i) if (!del[i]) {
		// cyclic paths
		int cur = i;
		++newEdges;
		while(true) {
			del[cur] = true;
			vec[newEdges].push_back(cur);
			cur = nxt[cur];
			if (cur == i) break;
		}
		G[fr[i]].push_back(make_pair(m + newEdges, fr[i]));
	}
}

void dfs(int u) {
	while(!G[u].empty()) {
		int v = G[u].back().second;
		int id = G[u].back().first;
		G[u].pop_back();
		E.push_back(id);
		dfs(v);
	}
}

void solve() {
	// check whether there exists a directed Eulerian cycle
	for (int i = 1; i <= n; ++i) {
		for (auto it : G[i]) ++in[it.second], ++out[i];
	}
	for (int i = 1; i <= n; ++i) if (in[i] != out[i]) invalid();

	// find a directed Eulerian cycle
	dfs(1);
	
	// trace
	ans.push_back(1);
	for (int id : E) {
		if (id <= m) ans.push_back(to[id]);
		else {
			for (int nId : vec[id - m]) {
				ans.push_back(to[nId]);
			}
		}
	}

	// re-check
	memset(del, 0, sizeof del);
	for (int id : ans) {
		if (del[id]) invalid(); del[id] = true;
	}
	for (int i = 1; i <= m; ++i) if (!del[i]) invalid();

	// output
	printf("TAK\n");
	for (int u : ans) printf("%d\n", u);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		mp[u][v] = i;
		fr[i] = u; to[i] = v;
	}
	init();
	compress();
	solve();
}