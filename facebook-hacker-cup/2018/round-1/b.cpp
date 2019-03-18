#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int n, k;
int val[N];
int l[N], r[N];
int pre[N], post[N];
int ptr_pre, ptr_post;

void dfs(int u) {
	if (u == 0) return;
	pre[++ptr_pre] = u;
	dfs(l[u]);
	dfs(r[u]);
	post[++ptr_post] = u;
}

// DSU
int par[N];
int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) {
	p = anc(p), q = anc(q);
	par[p] = q;
}

void solve() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> l[i] >> r[i];
	}
	ptr_pre = ptr_post = 0;
	dfs(1);

	for (int i = 1; i <= n; ++i) {
		par[i] = i;
	}
	for (int i = 1; i <= n; ++i) {
		if (pre[i] != post[i]) {
			join(pre[i], post[i]);
		}
	}

	int cur = 0;
	for (int i = 1; i <= n; ++i) if (anc(i) == i) {
		val[i] = cur % k + 1;
		++cur;
	}
	if (cur < k) {
		printf("Impossible\n");
		return;
	}

	for (int i = 1; i <= n; ++i) {
		val[i] = val[anc(i)];
		printf("%d ", val[i]);
	}
	printf("\n");
}

int main() {
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;
	for (int itest = 1; itest <= ntest; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}