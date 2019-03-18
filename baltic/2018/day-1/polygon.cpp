#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int INF = 1e9;

int n, deg[N], p[N];
bool del[N], vis[N];
vector <int> g[N];
int res;
vector <int> comp;
map <string, int> mp; int id;

int f[N][2];
int dp[N][2][2];

void dfs(int u) {
	comp.push_back(u);
	for (auto &v : g[u]) {
		if (deg[v] == 0) dfs(v);
	}
}

int calc(int u) {
	int ret = 0;
	for (auto &v : g[u]) if (deg[v] == 0) {
		ret += calc(v);
		if (!del[v] && !del[u]) ++ret, del[v] = del[u] = true;
	}
	return ret;
}

void find(int u) {
	vis[u] = true;
	comp.push_back(u);
	int v = p[u];
	if (deg[v] > 0 && !vis[v]) {
		return find(v);
	}
}

void maximize(int &x, int y) {
	x = (x > y) ? x : y;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	if (n & 1) return printf("-1\n"), 0;

	for (int i = 1; i <= n; ++i) {
		string s, t; cin >> s >> t;
		if (mp.find(s) == mp.end()) mp[s] = ++id;
		if (mp.find(t) == mp.end()) mp[t] = ++id;

		int u = mp[s], v = mp[t];
		p[u] = v;
		g[v].push_back(u);
		++deg[v];
	}

	queue <int> q;
	for (int i = 1; i <= n; ++i) if (!deg[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		int v = p[u];
		if (--deg[v] == 0) {
			q.push(v);
		}
	}

	for (int i = 1; i <= n; ++i) if (deg[i] > 0) { // root
		comp.clear();
		dfs(i);
		int c1 = calc(i);
		
		for (auto &v : comp) del[v] = false;
		int c0 = 0;
		for (auto &v : g[i]) if (deg[v] == 0) c0 += calc(v);

		f[i][1] = c1;
		f[i][0] = c0;
	}

	for (int i = 1; i <= n; ++i) if (deg[i] && !vis[i]) {
		comp.clear();
		find(i);
		if (comp.size() == 1) {
			res += f[comp[0]][1];
			continue;
		}
		if (comp.size() == 2) {
			int cur = -INF;
			cur = max(cur, f[comp[1]][1] + f[comp[0]][1]);
			cur = max(cur, f[comp[0]][0] + f[comp[1]][0] + 2);
			res += cur;
			continue;
		}

		int sz = comp.size();
		for (int j = 0; j < sz; ++j) for (int k = 0; k < 2; ++k) for (int l = 0; l < 2; ++l) dp[j][k][l] = -INF;
		dp[0][0][0] = f[comp[0]][0];
		dp[0][1][1] = f[comp[0]][1];

		for (int j = 1; j < sz; ++j) {
			for (int last = 0; last < 2; ++last) {
				for (int fi = 0; fi < 2; ++fi) {
					if (dp[j - 1][last][fi] == -INF) continue;

					for (int nxt = 0; nxt < 2; ++nxt) {
						maximize(dp[j][nxt][fi], dp[j - 1][last][fi] + f[comp[j]][nxt]);
						if (nxt) {
							if (!last) { // nxt - last
								int nfi = fi;
								if (j == 1) nfi = 1;
								maximize(dp[j][nxt][nfi], dp[j - 1][last][fi] + f[comp[j]][0] + 1);
							}
							if (j == sz - 1 && !fi) {
								maximize(dp[j][nxt][1], dp[j - 1][last][fi] + f[comp[j]][0] + 1);
							}
						}
					}
				}
			}
		}

		int cur = -INF;
		for (int last = 0; last < 2; ++last) {
			for (int fi = 0; fi < 2; ++fi) {
				cur = max(cur, dp[sz - 1][last][fi]);
			}
		}
		res += cur;
	}

	printf("%d\n", n - res);
}