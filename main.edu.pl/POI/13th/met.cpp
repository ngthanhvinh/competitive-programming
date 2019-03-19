#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, l;
vector<int> G[N];
int cnt[N];
int ans;

int dfs(int u, int p) {
	int mx = 0;
	for (int v : G[u]) if (v != p) {
		int k = dfs(v, u);
		++cnt[k];
		mx = max(mx, k);
	}
	if (mx > 0) cnt[mx]--;
	return mx + 1;
}

int bfs() {
	queue< pair<int,int> > q;
	q.push(make_pair(1,-1));
	int res;
	while(!q.empty()) {
		int u = q.front().first, p = q.front().second; q.pop();
		res = u;
		for (int v : G[u]) if (v != p) q.push(make_pair(v, u));
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &l);
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	++cnt[dfs(bfs(),-1)];
	l = 2 * l - 1;
	for (int i = n; i >= 1; --i) {
		while(l > 0 && cnt[i]) {
			--l;
			--cnt[i];
			ans += i;
		}
	}
	cout << ans << '\n';
}