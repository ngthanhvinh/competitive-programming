#include <bits/stdc++.h>
using namespace std;
const int N = 201;

int n, a[N][N];
int t, match[N], vis[N];

bool dfs(int u, int x) {
	if (vis[u] != t) vis[u] = t; else return 0;
	for (int i = 1; i <= n; i++) {
		if (a[u][i] > x) continue;
		if (!match[i] || dfs(match[i], x)) { match[i] = u; return 1; }
	}
	return 0;
}

bool f(int x) {
	memset(match, 0, sizeof match); memset(vis, 0, sizeof vis); t = 0;
	int res = 0;
	for (int i = 1; i <= n; i++) { t++; res += dfs(i, x); }
	//cout << res << "\n";
	return (res == n);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; 
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> a[i][j];
	int l = 0, r = 1e9;
	while(l != r) {
		int mid = ((l + r) >> 1);
		if (f(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
}