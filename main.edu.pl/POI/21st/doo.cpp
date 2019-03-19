#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, s;
int nxt[N];
int sum[N << 1];
int par[N];

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) {
	p = anc(p), q = anc(q);
	par[p] = q;
}

int dfs(int u) {
	int cnt = 0, cur = 0;
	while (1) {
		int tmp = nxt[u];
		int val = sum[tmp - 1] - sum[u - 1];
		if (tmp > n) tmp -= n;
		cur += val, u = tmp, cnt++;
		if (cur >= sum[n]) return cnt;
	}
}

void solve(int d) {
	int ptr = 1;
	for (int i = 1; i <= n; ++i) {
		while(sum[ptr] - sum[i-1] <= d) ++ptr; 
		nxt[i] = ptr;
		if (i == ptr) {
			printf("NIE\n"); return;
		}
	}

	int ans = 1e9;
	for (int i = 1; i <= n; ++i) par[i] = i;
	for (int i = 1; i <= n; ++i) {
		int tmp = nxt[i];
		if (tmp > n) tmp -= n;
		if (anc(i) == anc(tmp)) {
			ans = min(ans, dfs(i));
		} else join(i, tmp);
	}

	printf("%d\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> s;
	for (int i = 1; i <= n; ++i) cin >> sum[i];
	for (int i = 1; i <= n; ++i) sum[i+n] = sum[i];
	for (int i = 1; i <= n * 2; ++i) sum[i] = sum[i-1] + sum[i];

	while(s--) {
		int d; cin >> d;
		solve(d);
	}
}