#include <bits/stdc++.h>
using namespace std;

const int N = 50010;
const int M = 100010;

int n;
vector< pair<int,int> > G[N];
vector<int> two[M];
int cnt[2];
int ans;
int color[N];
int x[N], y[N];

void dfs(int u, int c) {
	++cnt[c];
	for (auto &edge : G[u]) {
		int v = edge.second, type = edge.first;
		if (color[v] != -1) continue;
		color[v] = (c ^ type);
		dfs(v, c ^ type);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> x[i], two[x[i]].push_back(i);
	for (int i = 1; i <= n; ++i) cin >> y[i], two[y[i]].push_back(-i);
	memset(color, -1, sizeof color);

	for (int val = 1; val < M; ++val) if (two[val].size() == 2) {
		int u = two[val][0], v = two[val][1];
		if (1LL * u * v > 0) {
			u = abs(u), v = abs(v);
			G[u].push_back(make_pair(1, v));
			G[v].push_back(make_pair(1, u));
		} else {
			u = abs(u), v = abs(v);
			G[u].push_back(make_pair(0, v));
			G[v].push_back(make_pair(0, u));
		}
	}
	
	for (int val = 1; val < M; ++val) if (color[val] == -1) {
		cnt[0] = cnt[1] = 0; color[val] = 0; dfs(val, 0);
		ans += min(cnt[0], cnt[1]);
	}

	cout << ans << endl;
}