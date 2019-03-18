#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q, root;
vector<int> G[N];
int mn[N];
int tout[N], euler[N], TIME, dep[N], par[N][18];
priority_queue < int, vector<int>, greater<int> > avail;
bool inQueue[N];

void prepare(int u) {
	mn[u] = u;
	for (int v : G[u]) {
		prepare(v);
		mn[u] = min(mn[u], mn[v]);
	}
}

void dfs(int u) {
	sort(G[u].begin(), G[u].end(), [&](int x, int y) {
		return mn[x] < mn[y];
	});
	for (int v : G[u]) {
		dep[v] = dep[u] + 1;
		par[v][0] = u;
		dfs(v);
	}
	tout[u] = ++TIME;
	euler[TIME] = u;
}

int jump(int x) {
	for (int i = 17; i >= 0; --i) if (!inQueue[par[x][i]]) x = par[x][i];
	return x;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		int p; cin >> p;
		if (p == 0) root = i; else G[p].push_back(i);
	}
	prepare(root);
	par[root][0] = root;
	dfs(root);
	for (int j = 1; j < 18; ++j) {
		for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j-1]][j-1];
	}
	
	for (int i = 1; i <= n; ++i) avail.push(i), inQueue[i] = true; // all nodes are initially available

	while(q--) {
		int type; cin >> type;
		if (type == 1) {
			int k; cin >> k; // the number of balls to be added
			int lst = 0; // the node contains the last ball
			while(k-- > 0) {
				int t = avail.top(); 
				lst = euler[t];
				inQueue[lst] = false;
				avail.pop();
			}
			printf("%d\n", lst);
		} else {
			int x; cin >> x; // the ball is going to be removed
			int p = jump(x); // jump to the lowest parent which has all nodes filled
			avail.push(tout[p]);
			inQueue[p] = true;
			printf("%d\n", dep[x] - dep[p]);
		}
	}
}