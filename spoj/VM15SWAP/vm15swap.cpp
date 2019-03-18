#include <bits/stdc++.h>
using namespace std;

const int N = 1001;
typedef pair <int, int> ii;
typedef vector <int> vi;
#define fi first
#define se second
int n, m, rMatch[N], vis[N], t, lMatch[N];
int check[2][N];
int matchingEdge[N][N];
int a[N][N];
int MinCover;
vector <ii> L, R, Z, K, I;
bool exist[2][N];
vector <vi> G, P;

bool findMatching(int u) {
	if (vis[u] != t) vis[u] = t; else return 0;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!rMatch[v] || findMatching(rMatch[v])) { rMatch[v] = u; return 1; }
	}
	return 0;
} 
// Left is 0, Right is 1
#define LEFT 0
#define RIGHT 1

void dfs(int u, bool g, bool e) {
	check[g][u] = 1;
	// u is the vertex, g is the set contains u (Left or Right), e is the type of the current edge (matching edge or not)
	if (g == LEFT) { // row set
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (matchingEdge[u][v] == (e ^ 1) && !check[RIGHT][v]) dfs(v, RIGHT, e^1);
		}
	}
	else {
		for (int i = 0; i < P[u].size(); i++) {
			int v = P[u][i];
			if (matchingEdge[v][u] == (e ^ 1) && !check[LEFT][v]) dfs(v, LEFT, e^1);
		}
	}
}

void process() {
	vector <int> pos;
	for (int i = 0; i < Z.size(); i++) {
		for (int j = L.size() - 1; j >= 0; j--) {
			if (L[j] == Z[i]) pos.push_back(j); 
		}
	}
	sort(pos.begin(), pos.end(), greater<int>());
	for (int j = 0; j < pos.size(); j++) L.erase(L.begin() + pos[j]);
	
	for (int i = 0; i < Z.size(); i++) exist[Z[i].fi][Z[i].se] = 1;
	for (int i = R.size() - 1; i >= 0; i--) if (!exist[R[i].fi][R[i].se]) R.erase(R.begin() + i);
	memset(exist, 0, sizeof exist);
	for (int i = 0; i < L.size(); i++) if (!exist[L[i].fi][L[i].se]) { K.push_back(L[i]); exist[L[i].fi][L[i].se] = 1; }
	for (int i = 0; i < R.size(); i++) if (!exist[R[i].fi][R[i].se]) { K.push_back(R[i]); exist[R[i].fi][R[i].se] = 1; }
	
	for (int i = 1; i <= n; i++) if (!exist[LEFT][i]) I.push_back(ii(LEFT, i));
	for (int i = 1; i <= m; i++) if (!exist[RIGHT][i]) I.push_back(ii(RIGHT, i));
}

void solve() {
	int r = 0, c = 0;
	for (int i = 0; i < I.size(); i++) if (I[i].fi == 0) r++; else c++;
	printf("%d %d\n", r, c);
	r = c = 0;
	printf("%d\n", (int)I.size());
	for (int i = 0; i < I.size(); i++) {
		if (I[i].fi == 0) { printf("R %d %d\n", I[i].se, ++r); }
		else { printf("C %d %d\n", I[i].se, ++c); }
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m; G.assign(n + 1, vi()); P.assign(m + 1, vi());
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j], a[i][j] ^= 1;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j]) G[i].push_back(j), P[j].push_back(i);
	for (int i = 1; i <= n; i++) { t++; MinCover += findMatching(i); }
	if (m + n - MinCover <= max(n, m)) return printf("0 0\n"), 0;

	for (int i = 1; i <= m; i++) if (rMatch[i]) { matchingEdge[rMatch[i]][i] = 1; lMatch[rMatch[i]] = i; }
	
	for (int i = 1; i <= n; i++) {
		if (lMatch[i]) continue;
		dfs(i, LEFT, 1);
	}

	for (int i = 1; i <= n; i++) { L.push_back(ii(LEFT, i)); if (check[LEFT][i]) Z.push_back(ii(LEFT, i)); }
	for (int i = 1; i <= m; i++) { R.push_back(ii(RIGHT, i)); if (check[RIGHT][i]) Z.push_back(ii(RIGHT, i)); }

	process();	
	solve();
}