#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int N, M, C[maxn], L[maxn];
int f[maxn];
vector <int> G[maxn];
multiset <int> S[maxn];
long long ans;

void solve(int u, int val) {
	if (f[u] >= val) f[u] -= val, S[u].insert(val);
	else if (!S[u].empty()) {
		multiset<int>::iterator IT = S[u].end(); --IT;
		if ((*IT) > val) f[u] += (*IT) - val, S[u].erase(IT), S[u].insert(val);
	}
}

void dfs(int u) {
	int mx = u, sz = 0; f[u] = M;
	for (int v: G[u]) {
		dfs(v);
		if (sz <= S[v].size()) sz = S[v].size(), mx = v; 
	}
	S[mx].swap(S[u]), f[u] = f[mx];

	solve(u, C[u]);
	for (int v: G[u]) if (v != mx) {
		for (multiset<int>::iterator it = S[v].begin(); it != S[v].end(); ++it) {
			int cur = (*it);
			solve(u, cur);
		}
	}

	ans = max(ans, 1ll * L[u] * (int)S[u].size());
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		int B; cin >> B >> C[i] >> L[i];
		G[B].push_back(i);
	}
	dfs(1);
	printf("%lld\n", ans);
}