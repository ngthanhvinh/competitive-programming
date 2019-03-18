#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const int inf = 1e9 + 7;

int n;
vector<int> G[N];
int d[N];

int bfs(int s) {
	queue<int> q; q.push(s); for (int i = 1; i <= n; ++i) d[i] = inf; d[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < (int)G[u].size(); ++i) {
			int v = G[u][i];
			if (d[v] > d[u] + 1) d[v] = d[u] + 1, q.push(v);
		}
	}
	int res = 0;
	for (int i = 1; i <= n; ++i) if (d[i] != inf) res += d[i]; else return inf;
	return res + n;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int k; cin >> k;
		while(k--) {
			int p; cin >> p; G[p].push_back(i);
		}
	}

	int ans = inf;
	for (int i = 1; i <= n; ++i) {
		ans = min(ans, bfs(i));
	}
	cout << ans << endl;
}