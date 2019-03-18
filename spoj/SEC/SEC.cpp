#include <bits/stdc++.h>
using namespace std;
const int N = 2;

int n, m, ans, cnt;
struct node {
	node *child[N]; int f, g; 
	node() { for (int i = 0; i < N; i++) child[i] = NULL; f = g = 0; }
	~node() { for (int i = 0; i < N; i++) delete child[i]; }
	void add(int x) { if (child[x] == NULL) child[x] = new node(); }
} *Trie = new node();

void add(int k) {
	node *cur = Trie;
	for (int i = 0; i < k; i++) {
		char x; cin >> x; cur -> add(x - '0'); 
		cur -> f++; cur = cur -> child[x - '0'];
	}
	cur -> g++;
}

void dfs(int k) {
	cnt = ans = 0; node *cur = Trie;
	for (int i = 0; i < k; i++) {
		char x; cin >> x; cnt++;
		cur = cur -> child[x - '0'];
		if (cur == NULL) break;
		ans += cur -> g;
	}
	for (int j = cnt + 1; j <= k; j++) { char x; cin >> x; }
	if (cur != NULL) ans += cur -> f;
	printf("%d\n", ans);
}

void solve() {
	cin >> m >> n;
	for (int i = 1; i <= m; i++) {
		int k; cin >> k;
		add(k);
	}
	for (int i = 1; i <= n; i++) {
		int k; cin >> k;
		dfs(k);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	solve();
}