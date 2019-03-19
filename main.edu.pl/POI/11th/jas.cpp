#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> G[50005];
int f[50005];
int ans;

void dfs(int u, int p) {
	int cnt[20] = {};

	for (int v : G[u]) if (v != p) {
		dfs(v, u);
		for (int i = 0; i < 20; ++i) cnt[i] += (f[v] >> i & 1);
	}

	int lst = -1;
	for (int i = 19; i >= 0; --i) {
		if (cnt[i] >= 2) { lst = i; break; }
	}
	for (int i = lst + 1; i < 20; ++i) {
		if (cnt[i] == 0) {
			ans = max(ans, i);
			for (int j = i + 1; j < 20; ++j) {
				if (cnt[j]) f[u] |= (1 << j);
			}
			f[u] |= (1 << i);
			return;
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}	
	dfs(1, 1);
	printf("%d\n", ans);
}