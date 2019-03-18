#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, dfs[N], bfs[N], pos[N];
bool vis[N];
int ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> dfs[i];
	for (int i = 1; i <= n; ++i) cin >> bfs[i], pos[bfs[i]] = i;
	for (int i = 1; i <= n; ++i) dfs[i] = pos[dfs[i]];

	for (int i = 1; i <= n; ++i) pos[dfs[i]] = i;

	vis[1] = vis[2] = 1;
	int l = 2, r = n + 1;

	for (int i = 3; i <= n; ++i) {
		if (pos[i] < pos[i - 1]) ans += 2; // 1
		else if (pos[i] == pos[i - 1] + 1) {
			if (l + n + 1 - r == i - 1) {
				ans += 1; // 0.5
			}
		}

		vis[pos[i]] = 1;
		while(l < n && vis[l + 1]) ++l;
		while(r > 1 && vis[r - 1]) --r;
	}

	ans += 4;

	printf("%d.%d\n", ans / 2, (ans % 2 == 0) ? 0 : 5);
}