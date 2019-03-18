#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int INF = 1e9;
const int mod = 1e9 + 7;

int n, k, a[N];
int d[N][N];
int res;
vector <int> g[N];

void bfs(int s) {
	for (int i = 1; i <= n; ++i) d[s][i] = INF;
	d[s][s] = 0;
	queue <int> q;
	q.push(s);

	int sz = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		a[++sz] = u;
		for (int &v : g[u]) if (d[s][v] == INF) {
			d[s][v] = d[s][u] + 1;
			q.push(v);
		}
	}
}

bool check(int x) {
	res = 1;
	for (int i = 1; i <= n; ++i) {
		int cnt = 0;
		for (int j = 1; j <= i - 1; ++j) {
			if (d[a[i]][a[j]] < x) ++cnt;
		}
		int mul = max(0, k - cnt);
		if (!mul) return false;
		res = 1LL * res * mul % mod;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> k;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int i = n; i >= 1; --i) {
		bfs(i);
	}

	int low = 1, high = n - 1;
	while(low < high) {
		int mid = ((low + high + 1) >> 1);
		if (check(mid)) low = mid;
		else high = mid - 1;
	}

	check(low);
	printf("%d %d\n", low, res);
}