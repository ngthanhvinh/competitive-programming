#include <bits/stdc++.h>
using namespace std;

const int N = 7e4 + 5;

int n, dep[N], par[N][18], tin[N], tout[N], TIME;
vector<int> G[N];
vector<int> save[3 * N];
int sz;
map < pair<int,int>, int > mp;
map <int, int> mn[N];
int dis[N];

bool check[N];

void prep(int u, int p) {
	tin[u] = ++TIME;
	for (int v : G[u]) if (v != p) {
		par[v][0] = u;
		dep[v] = dep[u] + 1;
		prep(v, u);
	}
	tout[u] = TIME;
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 17; i >= 0; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
	for (int i = 17; i >= 0; --i) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
	return u == v ? u : par[u][0];
}

int dist(int u, int v) {
	return dep[u] + dep[v] - 2 * dep[lca(u,v)];
}

int get_par(int u, int root) {
	if (u == root) return root;
	if (tin[u] >= tin[root] && tin[u] <= tout[root]) {
		return par[u][0];
	}
	
	int x = lca(u, root);
	if (x != u) {
		return par[u][0];
	}
	for (int i = 17; i >= 0; --i) 
		if (dep[par[root][i]] > dep[u]) root = par[root][i];
	
	return root;
}

set < pair<int,int> > seg;

bool not_in_seg(int u) {
	set< pair<int,int> >::iterator it = seg.upper_bound(make_pair(tin[u], 1e9));
	if (it == seg.begin()) {
		return true;
	}
	--it;
	if ((*it).second >= tout[u]) return false; else return true;
}

void dfs(int u, int p) {
	if (mp.find(make_pair(u, p)) != mp.end()) return;
	mp[make_pair(u, p)] = ++sz;

	int id = sz;
	if (G[u].size() == 1) {
		save[id] = vector<int>(1, u); mn[u][p] = 0; return;
	}

	int minval = 1e9;
	int max_tin = -1e9, min_tout = 1e9;

	vector<int> new_save;
	for (int v : G[u]) if (v != p) {
		dfs(v, u);
		minval = min(minval, mn[v][u] + 1);
		int vv = mp[make_pair(v, u)];

		for (int w : save[vv]) {
			int pw = get_par(w, u);
			if (check[pw]) continue;

			if (pw != u && dist(u, pw) >= mn[pw][get_par(pw, u)]) {
				check[pw] = 1, new_save.push_back(pw);
			} else check[w] = 1, new_save.push_back(w); // todo: fix
		}
	}

	mn[u][p] = minval;
	for (int w : new_save) check[w] = 0, dis[w] = dist(u, w);
	sort(new_save.begin(), new_save.end(), [&](int x, int y) {
		return dis[x] < dis[y];
	});

	seg.clear();
	for (int w : new_save) {
		// check whether {w} is valid
		if (!not_in_seg(w)) continue;

		if (tin[w] < tin[u] || tin[w] > tout[u]) { // outside Subtree(u)
			if (max_tin >= tin[w] || tin[w] >= min_tout) continue;

			int pw = lca(u, w);
			if (w != pw) {
				seg.insert(make_pair(tin[w], tout[w])); save[id].push_back(w); continue;
			}

			max_tin = max(max_tin, tin[w]);
			min_tout = min(min_tout, tout[w]);

			pw = get_par(w, u);
			for (int v : G[w]) {
				if (v == par[w][0]) continue;
				if (tin[v] >= tin[pw] && tin[v] <= tout[pw]) continue;

				seg.insert(make_pair(tin[v], tout[v]));
			}
			seg.insert(make_pair(tin[w], tin[w]));
		} else { // inside Subtree(u)
			seg.insert(make_pair(tin[w], tout[w]));
		}
		save[id].push_back(w);
	}
}

int main() {
	freopen("atlarge.in", "r", stdin);
	freopen("atlarge.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}

	par[1][0] = 1;
	prep(1, 1);
	for (int j = 1; j <= 17; ++j) {
		for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j - 1]][j - 1];
	}
	
	for (int i = 1; i <= n; ++i) {
		if (G[i].size() == 1) {
			printf("1\n"); continue;
		}

		dfs(i, i);
		printf("%d\n", save[mp[make_pair(i, i)]].size());
	}
}