#include <bits/stdc++.h>
using namespace std;

const int N = 4005;
const int K = 105;
const int inf = 1e9;

int n, k;

struct Node {
	int ch[26];
	int f[K];
	int nChild;
	int ok;
	Node() { 
		memset(ch, -1, sizeof ch); 
		for (int i = 0; i < K; ++i) f[i] = inf;
		nChild = 0; ok = 0;
	}
};
Node Trie[20005];
int sz;

void add(string s) {
	int cur = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		if (Trie[cur].ch[s[i] - 'a'] == -1) {
			Trie[cur].ch[s[i] - 'a'] = ++sz;
			Trie[sz] = Node();
		}
		cur = Trie[cur].ch[s[i] - 'a'];
	}
	Trie[cur].ok = 1;
}

int g[K];
void dfs(int u) {
	Trie[u].nChild = 0;
	Trie[u].f[0] = 0;
	for (int i = 0; i < 26; ++i) if (Trie[u].ch[i] != -1) {
		int v = Trie[u].ch[i];
		dfs(v);
		for (int x = 0; x <= k; ++x) g[x] = inf;
		for (int x = 0; x <= min(Trie[u].nChild, k); ++x) 
			for (int y = 0; y <= min(Trie[v].nChild, k - x); ++y) {
				g[x + y] = min(Trie[u].f[x] + Trie[v].f[y], g[x + y]);
			}

		for (int x = 0; x <= k; ++x) Trie[u].f[x] = g[x];
		Trie[u].nChild += Trie[v].nChild;
	}
	for (int x = 0; x <= k; ++x) g[x] = inf;
	
	g[0] = 0;
	for (int x = 1; x <= min(k, Trie[u].nChild); ++x) g[x] = min(g[x], Trie[u].f[x] + x);
	for (int x = 0; x <= k; ++x) Trie[u].f[x] = g[x];

	Trie[u].nChild += Trie[u].ok;
	
	if (Trie[u].ok) {
		for (int x = 0; x <= k; ++x) g[x] = inf;
		g[0] = 0; for (int x = 0; x < min(k, Trie[u].nChild); ++x) g[x + 1] = min(g[x + 1], Trie[u].f[x] + 1);
		for (int x = 0; x <= k; ++x) Trie[u].f[x] = g[x];
	}
	if (Trie[u].nChild > 0) Trie[u].f[1] = 1;
}

int solve() {
	cin >> n >> k;
	sz = 0;
	Trie[0] = Node();
	for (int i = 1; i <= n; ++i) {
		string s; cin >> s;
		add(s);
	}
	dfs(0);
	return Trie[0].f[k] - k;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: %d\n", i, solve());
	}
}