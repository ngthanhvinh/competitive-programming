#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <stack>
using namespace std;

const int N = 500010, BASE = 26, MOD = 1e9 + 9;
typedef vector<int> vi;

int n, q, m, h[N], pw[N];
string s;
vector <vi> G;
map <int,int> pos;
int c[N];
int low[N], num[N], step;
stack <int> st;
int ans, a[N];

void dfs(int u) {
	low[u] = num[u] = ++step; st.push(u);
	int v = a[u]; if (num[v]) low[u] = min(low[u], num[v]); else dfs(v), low[u] = min(low[u], low[v]);
	if (low[u] == num[u]) {
		int v = 0, sum = 0, cnt = 0;
		do {
			v = st.top(); st.pop(); low[v] = num[v] = MOD; sum += c[v]; ++cnt;
		} while(v != u);
		if (cnt == 1 && a[u] == u) ans = max(ans, sum);
		else if (cnt != 1 && m % cnt == 0) ans = max(ans, sum);
	}
}

void solve() {
	pos.clear(); memset(c, 0, sizeof c); memset(low, 0, sizeof low); memset(num, 0, sizeof num); st = stack<int>(); step = 0; ans = 0; memset(a, 0, sizeof a);
	int cnt = 1; h[1] = 0;
	for (int i = 1; i <= m; ++i) h[1] = (1ll * h[1] * BASE + s[i] - 'A') % MOD; pos[h[1]] = 1, c[1]++;

	for (int i = 2; i <= n-m+1; ++i) {
		h[i] = ((h[i-1] - 1ll * pw[m-1] * (s[i-1]-'A') % MOD) + MOD) % MOD;
		h[i] = (1ll * BASE * h[i] + s[i+m-1] - 'A') % MOD;
		if (!pos.count(h[i])) pos[h[i]] = ++cnt; c[pos[h[i]]]++;
	}
	G.assign(cnt+1, vi());
	for (int i = 1; i <= n-m+1; ++i) {
		int hsh = ((h[i] - 1ll * pw[m-1] * (s[i]-'A') % MOD) + MOD) % MOD;
		hsh = (1ll * BASE * hsh + s[i] - 'A') % MOD;
		if (pos.count(hsh)) a[pos[h[i]]] = pos[hsh];
	}
	
	for (int i = 1; i <= cnt; ++i) if (!num[i]) dfs(i);
	printf("%d\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q >> s; s = ' ' + s;
	pw[0] = 1; for (int i = 1; i < N; ++i) pw[i] = 1ll * pw[i-1] * BASE % MOD;
	while(q--) {
		cin >> m;
		solve();
	}
}