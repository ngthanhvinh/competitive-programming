#include <bits/stdc++.h>
using namespace std;

const int N = 60005;
const int MAX = 600005;

int n, diff, a[N], s[N];
int par[N], nver[N], nedge[N];
vector < pair<int,int> > g[N];
int deg[N];
int sum;
bool del[N], vedge[N];
vector <int> cycle, weight;

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }

void add(int u, int v, int i) {
	g[u].push_back({v, i}); ++deg[u];
	g[v].push_back({u, i}); ++deg[v];
}

void find_cycle(int u, int r) {
	del[u] = true;
	cycle.push_back(u);
	for (auto &e : g[u]) if (!del[e.first]) {
		weight.push_back(s[e.second]);
		vedge[e.second] = true;
		return find_cycle(e.first, r);
	}
	// cannot visit any vertices
	for (auto &e : g[u]) if (e.first == r && !vedge[e.second]) {
		weight.push_back(s[e.second]);
	}
}

void dfs_tree(int u, int p) {
	if (u <= n) sum += a[u];
	for (auto &e : g[u]) {
		int v = e.first; if (v == p || deg[v] == 2) continue;
		dfs_tree(v, u);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> diff;

	for (int i = 1; i <= n + n; ++i) { // reset Disjoint Set
		par[i] = i;
		nver[i] = 1;
		nedge[i] = 0;
	}

	for (int i = 1; i <= n + n; ++i) {
		int u, v; cin >> u >> v >> s[i];
		v += n;
		int pu = anc(u), pv = anc(v);
		if (pu == pv) {
			if (nver[pu] > nedge[pu]) ++nedge[pu], add(u, v, i);
			else { // invalid
				return printf("NO\n"), 0;
			}
		} else { // join u and v
			nver[pu] += nver[pv]; nver[pv] = 0;
			nedge[pu] += nedge[pv] + 1; nedge[pv] = 0;
			par[pv] = pu;
			add(u, v, i);
			if (nver[pu] < nedge[pu]) {
				return printf("NO\n"), 0;
			}
		}
	}

	queue <int> q;
	for (int i = 1; i <= n + n; ++i) if (deg[i] == 1) q.push(i);

	while(!q.empty()) {
		int u = q.front(); q.pop();
		del[u] = true;
		for (auto &e : g[u]) {
			int v = e.first, w = s[e.second]; 
			if (del[v]) continue;
			a[u] = w;
			if (--deg[v] == 1) q.push(v);
		}
	}

	// DP
	bitset <MAX> bs;
	bs.set(0);

	for (int i = 1; i <= n + n; ++i) if (!del[i]) { // in cycle
		cycle.clear();
		weight.clear();
		find_cycle(i, i);
		sum = 0;
		for (int j : cycle) {
			dfs_tree(j, j);
		}

		int sz = cycle.size();
		int sum1 = 0, sum2 = 0;

		for (int i = 0; i < sz; ++i) {
			int w = weight[i];
			if (cycle[i] <= n) sum1 += w;
			if (cycle[(i + 1) % sz] <= n) sum2 += w;
		}

		// group 1
		int c = sum + sum1; // first choice
		int d = sum + sum2; // second choice
		bs = (bs << c) | (bs << d);
	}

	// check
	sum = 0;
	for (int i = 1; i <= n + n; ++i) sum += s[i];

	for (int i = 1; i <= sum; ++i) if (bs[i]) {
		int j = sum - i; // group 2
		if (abs(i - j) <= diff) {
			return printf("YES\n"), 0;		
		}
	}

	printf("NO\n");
}