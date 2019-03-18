#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1000005;
const int MAXN = 100005;

int nquery, nstr;
string a;
int which[MAXN];
bool state[MAXN];

// Trie
struct Node {
	int ch[26];
	Node() {
		memset(ch, 0, sizeof ch);
	}
} trie[MAXLEN];
int sz;

// Aho Corasick
int fail[MAXLEN];
vector <int> g[MAXLEN];
int tin[MAXLEN], tout[MAXLEN], TIME;

void add(string &s, int id) {
	int cur = 0;
	for (int i = 0; i < s.size(); ++i) {
		int c = s[i] - 'a';
		if (trie[cur].ch[c] == 0) {
			trie[cur].ch[c] = ++sz;
		}
		cur = trie[cur].ch[c];
	}
	which[id] = cur;
}

void bfs() {
	queue <int> q; q.push(0);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; ++i) {
			int v = trie[u].ch[i];
			trie[u].ch[i] = 0;
			trie[u].ch[i] = trie[fail[u]].ch[i];
			if (v) {
				fail[v] = trie[u].ch[i];
				trie[u].ch[i] = v;
				q.push(v);
			}
		}
	}
}

void dfs(int u) {
	tin[u] = ++TIME;
	for (int &v : g[u]) dfs(v);
	tout[u] = TIME;
}

void prepare() {
	// build link-tree
	for (int i = 1; i <= sz; ++i) {
		g[fail[i]].push_back(i);
	}
	dfs(0);
}

// ------------------------------------------------------------------------------------
struct FenwickTree {
	int T[MAXLEN];
	FenwickTree() { memset(T, 0, sizeof T); }
	void upd(int x, int v) { for (; x <= TIME; x += x & -x) T[x] += v; }
	int get(int x) { int ret = 0; for (; x > 0; x -= x & -x) ret += T[x]; return ret; }
} bit;

void upd(int x, int v) {
	bit.upd(tin[x], v);
	bit.upd(tout[x] + 1, -v);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> nquery >> nstr;
	for (int i = 1; i <= nstr; ++i) {
		cin >> a;
		add(a, i);
	}

	bfs();
	prepare();

	for (int i = 1; i <= nstr; ++i) {
		upd(which[i], 1);
		state[i] = 1;
	}

	while(nquery--) {
		string s; cin >> s;
		if (s[0] == '?') {
			s.erase(s.begin());
			int cur = 0;
			long long res = 0;
			for (int i = 0; i < s.size(); ++i) {
				int c = s[i] - 'a';
				cur = trie[cur].ch[c];
				res += bit.get(tin[cur]);
			}

			printf("%lld\n", res);
		} else {
			int val = 0;
			for (int i = 1; i < s.size(); ++i) {
				val = 10 * val + s[i] - '0';
			}

			if (s[0] == '-') {
				if (state[val]) state[val] = 0, upd(which[val], -1);
			} else {
				if (!state[val]) state[val] = 1, upd(which[val], +1);
			}
		}
	}
}