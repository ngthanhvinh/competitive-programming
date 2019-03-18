#include <bits/stdc++.h>
using namespace std;

const int N = 300005;
typedef pair<int,int> ii;
#define fi first
#define se second

int n, m;
vector<ii> G[N];
int A[N], B[N];
int par[N], toPar[N];
int dir[N << 1];

struct Answer {
	int type; int u; int v;
	Answer(int type=0, int u=0, int v=0): type(type), u(u), v(v) {}
};
vector<Answer> ans;

void change(int v) {
	int id = toPar[v];
	if (dir[id]) ans.push_back(Answer(1, v, par[v]));
	else ans.push_back(Answer(1, par[v], v));
	dir[id] ^= 1; dir[id ^ 1] ^= 1;
}

int dfs(int u) {	
	vector<int> vec;
	if (A[u]) vec.push_back(u);
	for (auto &edge: G[u]) {
		int v = edge.se; if (par[v]) continue;
		par[v] = u;
		toPar[v] = (edge.fi ^ 1);
		int cur = dfs(v);
		if (cur) vec.push_back(cur);
	}

	while(vec.size() > 1) {
		int v = vec.back(); vec.pop_back();
		int w = vec.back(); vec.pop_back();
		while(v != u) change(v), v = par[v];
		while(w != u) change(w), w = par[w];
	}
	if (vec.size() == 1) return vec[0]; else return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(ii(2 * i, v)); G[v].push_back(ii(2 * i + 1, u));	
		dir[2 * i] = 1, dir[2 * i + 1] = 0;
		A[u] = (A[u] + 1) % 2; B[v] = (B[v] + 1) % 2;
 	}

 	for (int i = 1; i <= n; ++i) if (par[i] == 0) {
 		par[i] = i;
 		int res = dfs(i);
 		if (res) return printf("-1\n"), 0;
 	}

 	vector<int> odd;
 	for (int i = 1; i <= n; ++i) {
 		B[i] = (A[i] != B[i]);
 		if (B[i]) odd.push_back(i);
 	}
 	if (odd.size() & 1) return printf("-1\n"), 0;

 	for (int i = 0; i < (int)odd.size(); i += 2) {
 		ans.push_back(Answer(2, odd[i], odd[i+1]));
 	}
 	for (int i = 1; i <= n; ++i) ans.push_back(Answer(2, i, i % n + 1));
 	printf("%d\n", (int)ans.size());
 	for (int i = 0; i < (int)ans.size(); ++i) {
 		printf("%d %d %d\n", ans[i].type, ans[i].u, ans[i].v);
 	}
}