#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int M = 500005;

int n, m;
vector< pair<int,int> > G[N]; // (edge, vertex)
vector< pair<int,int> > cyc; // (vertex, edge)
int a[N], del[N], deg[N];
long long w[M];

void find_cycle(int u, int r) {
	del[u] = 1;
	for (auto e : G[u]) {
		if (!del[e.second]) {
			cyc.push_back(make_pair(u, e.first));
			return find_cycle(e.second, r);
		}
	}
	for (auto e : G[u]) {
		if (e.second == r) {
			cyc.push_back(make_pair(u, e.first));
			return;
		}
	}
}

void dfs(int u) {
	for (auto e : G[u]) {
		int v = e.second;
		if (del[v]) {
			w[e.first] = a[v], a[u] -= w[e.first];
		}
	}
}

void out() {
	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", 2LL * w[i]);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	if (n < m) return printf("0\n"), 0; // invalid
	// ------------- init -------------------------
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(make_pair(i,v));
		G[v].push_back(make_pair(i,u));
		++deg[u]; ++deg[v];
	}

	// ---------- find cycle ------------------------------------
	queue <int> q;
	for (int i = 1; i <= n; ++i) {
		if (deg[i] == 1) q.push(i);
	}
	while(!q.empty()) {
		int u = q.front(); q.pop(); del[u] = 1;
		dfs(u); // for subtree
		for (auto e : G[u]) if (!del[e.second]) {
			int v = e.second;
			if (--deg[v] == 1) q.push(v);
		}
	}
	for (int i = 1; i <= n; ++i) if (!del[i]) dfs(i); // roots of the subtrees
	for (int i = 1; i <= n; ++i) if (!del[i]) {
		find_cycle(i, i); break;
	}

	// ----- find the weights of the edges ----------------------------------------------------
	if (cyc.size() == 0) { // tree
		out();
		return 0;
	}
	if (cyc.size() % 2 == 0) return printf("0\n"), 0; // invalid

	// solve in the cycle
	int sz = cyc.size();
	int cur = 0;
	long long sum = 0;
	long long weight = 0;
	long long cursum = 0;
	// first: vertex
	// second: edge
	while(true) {
		if ((cur + 2) % sz == 0) break;
		cursum += a[cyc[(cur + 1) % sz].first] - a[cyc[(cur + 2) % sz].first];
		weight += cursum;
		cur = (cur + 2) % sz;
	}
	for (int i = 0; i < sz; ++i) sum += a[cyc[i].first]; sum /= 2; // sum of weights of the edges
	w[cyc[0].second] = (sum + weight) / sz;
	cur = 0;
	cursum = 0;
	while(true) {
		cursum += a[cyc[(cur + 1) % sz].first] - a[cyc[(cur + 2) % sz].first];
		cur = (cur + 2) % sz;
		if (cur == 0) break;
		w[cyc[cur].second] = w[cyc[0].second] - cursum;
	}

	out();
}