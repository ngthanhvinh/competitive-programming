#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n, a[N], c[N];
vector <int> R[N];
int deg[N], vis[N];
vector <int> comp;
int mx[N], t[N];
long long sum[N];
long long res;
long long ans = 0;

void find_cycle(int u, int r) {
	vis[u] = 1; comp.push_back(u);
	if (a[u] == r) return;
	find_cycle(a[u], r);
}

void dfs(int u) {
	res += c[u];
	for (int v: R[u]) {
		if (!vis[v]) dfs(v), sum[u] += sum[v], mx[u] = max(mx[u], c[v]);
	}
	sum[u] += mx[u];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i] >> c[i], deg[a[i]]++, R[a[i]].push_back(i);
	queue <int> qu;
	for (int i = 1; i <= n; ++i) if (!deg[i]) qu.push(i);
	while(!qu.empty()) {
		int u = qu.front(); qu.pop();
		if (deg[a[u]]) deg[a[u]]--;
		if (!deg[a[u]]) qu.push(a[u]);
	}
	for (int i = 1; i <= n; ++i) if (deg[i] && !vis[i]) {
		comp.clear(), find_cycle(i,i);
		if (comp.size() == n) return cout << 0 << endl, 0;
		res = 0;
		long long cur = 1e18;
		for (int u: comp) dfs(u), sum[u] -= mx[u], res -= sum[u];
		for (int i = 0; i < comp.size(); ++i) {
			t[comp[i]] = mx[comp[i]];
			if (i > 0) t[comp[i]] = max(t[comp[i]], c[comp[i-1]]);
			res -= t[comp[i]];
		}
		cur = min(cur, res);
		for (int i = 1; i < comp.size(); ++i) {
			int u = comp[i-1]; res += t[u];
			int v = comp[i]; res += t[v];
			t[u] = max(mx[u], c[comp[(i-2+(int)comp.size()) % (int)comp.size()]]);
			t[v] = mx[v];
			res -= t[u]; res -= t[v];
			cur = min(cur, res);
		}
		ans += cur;
	}

	cout << ans << endl;
}