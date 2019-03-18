#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int INF = 1e9;

int n, m;
int low[N], num[N], step, dep[N];
bool from[N];
int pair_ok[4][4], mask_ok[4][8];
vector <int> g[N];
vector <int> tree[N];

void dfs(int u, int p) {
	num[u] = low[u] = ++step;
	int cnt_up = 0;
	int cnt_down = 0;
	for (int &v : g[u]) if (v != p) {
		if (num[v]) {
			if (dep[v] < dep[u]) ++cnt_up, from[u] = true;
			low[u] = min(low[u], num[v]);
		}
		else {
			dep[v] = dep[u] + 1;
			tree[u].push_back(v);
			dfs(v, u);
			if (low[v] < num[u]) ++cnt_down, low[u] = low[v];
		}
	}

	if (cnt_up > 1 || cnt_down > 1) { printf("-1\n"); exit(0); }
	// invalid <-> not cactus
}

void minimize(int &x, int y) {
	x = (x > y) ? y : x;
}

int dp[N][4][8][2];
int tmp[4][8][2];
void solve(int u, int p) { // DP
	for (int up = 0; up < 4; ++up) for (int mask = 0; mask < 8; ++mask) for (int mod2 = 0; mod2 < 2; ++mod2) dp[u][up][mask][mod2] = INF;
	dp[u][3][0][0] = 0; // [no up][mask = 0][mod2 = 0]
	
	for (int &v : tree[u]) {
		solve(v, u);

		for (int up = 0; up < 4; ++up) for (int mask = 0; mask < 8; ++mask) for (int mod2 = 0; mod2 < 2; ++mod2) {
			tmp[up][mask][mod2] = INF;
		}

		for (int up_v = 0; up_v < 4; ++up_v) for (int mask_v = 0; mask_v < 8; ++mask_v) for (int mod2_v = 0; mod2_v < 2; ++mod2_v) {
			if (dp[v][up_v][mask_v][mod2_v] == INF) continue;
		
			for (int vu = 0; vu < 3; ++vu) { // 0, 1, 2
				if (!mask_ok[vu][mask_v]) continue; // "mask_ok" with mask_v

				// update
				for (int mask_u = 0; mask_u < 8; ++mask_u) if (mask_ok[vu][mask_u]) {
					for (int up_u = 0; up_u < 4; ++up_u) for (int mod2_u = 0; mod2_u < 2; ++mod2_u) {
						if (dp[u][up_u][mask_u][mod2_u] == INF) continue;
						if (low[v] == num[u]) { // stops at u
							if (pair_ok[vu][up_v] && mask_ok[up_v][mask_u] && (mod2_v + vu) % 2 == 1) { // can be used
								minimize(tmp[up_u][mask_u | (1 << up_v) | (1 << vu)][mod2_u], dp[v][up_v][mask_v][mod2_v] + dp[u][up_u][mask_u][mod2_u] + vu);
							}
						}
						else if (low[v] < num[u]) { // continues going
							assert(up_u == 3 && mod2_u == 0);
							minimize(tmp[up_v][mask_u | (1 << vu)][(mod2_v + vu) % 2], dp[v][up_v][mask_v][mod2_v] + dp[u][up_u][mask_u][mod2_u] + vu);
						}
						else { // bridge
							minimize(tmp[up_u][mask_u | (1 << vu)][mod2_u], dp[v][up_v][mask_v][mod2_v] + dp[u][up_u][mask_u][mod2_u] + vu);
						}
					}
				}
			}
		}

		for (int up = 0; up < 4; ++up) for (int mask = 0; mask < 8; ++mask) for (int mod2 = 0; mod2 < 2; ++mod2) {
			dp[u][up][mask][mod2] = tmp[up][mask][mod2];
		}
	}

	if (from[u]) {
		for (int up = 0; up < 4; ++up) for (int mask = 0; mask < 8; ++mask) tmp[up][mask][0] = tmp[up][mask][1] = INF;
		for (int up = 0; up < 3; ++up) for (int mask = 0; mask < 8; ++mask) {
			if (mask_ok[up][mask]) minimize(tmp[up][mask | (1 << up)][up == 1], dp[u][3][mask][0] + up);
		}
		for (int up = 0; up < 4; ++up) for (int mask = 0; mask < 8; ++mask) for (int mod2 = 0; mod2 < 2; ++mod2) dp[u][up][mask][mod2] = tmp[up][mask][mod2];
	}

	// debug
	// for (int up = 0; up < 4; ++up) for (int mask = 0; mask < 8; ++mask) for (int mod2 = 0; mod2 < 2; ++mod2) {
	// 	if (dp[u][up][mask][mod2] == INF) continue;
	// 	printf("u = %d up = %d mod2 = %d, mask = %d", u, up, mod2, mask);
	// 	printf("\tdp = %d\n", dp[u][up][mask][mod2]);
	// }
}

void prepare() {
	// pair_ok
	for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
		if (i == 3 || j == 3) pair_ok[i][j] = true;
		else if ((i + j) % 3 != 1) pair_ok[i][j] = true;
	}
	// mask_ok
	for (int i = 0; i < 4; ++i) for (int mask = 0; mask < 8; ++mask) {
		bool flag = true;
		for (int j = 0; j < 3; ++j) for (int k = 0; k < 3; ++k) { // check mask
			if (j != k && (mask >> j & 1) && (mask >> k & 1) && (j + k) % 3 == 1) flag = false;
		}
		if (!flag) continue;
		if (i == 3) { mask_ok[i][mask] = true; continue; }
		for (int j = 0; j < 3; ++j) if (mask >> j & 1) {
			if ((i + j) % 3 == 1) flag = false;
		}
		if (flag) mask_ok[i][mask] = true;
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	prepare();
	cin >> n >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	int res = 0;
	for (int i = 1; i <= n; ++i) if (!num[i]) {
		dfs(i, i);
		solve(i, i);
		int mn = INF;
		for (int mask = 0; mask < 8; ++mask) {
			mn = min(mn, dp[i][3][mask][0]);
		}
		res += mn;
	}

	printf("%d\n", res);
}