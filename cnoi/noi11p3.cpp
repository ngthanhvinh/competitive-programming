// http://wcipeg.com/problem/noi11p3
// Day 1, Problem 3 - Ali's Typewriter

#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int n, nquery, pos[N], ans[N];
vector<int> all[N];
vector< pair<int,int> > Q[N];

// Aho Corasick
struct node {
	int par; int ch[26];	
} trie[N];
int cur = 0; // starting from the root of trie
int sz = 1;

void add(int c) {
	if (trie[cur].ch[c] == 0) trie[cur].ch[c] = sz++, trie[sz - 1].par = cur;
	cur = trie[cur].ch[c];
}

int fail[N], nxt[N][26];
void bfs() {
	queue <int> q; q.push(0);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; ++i) {
			nxt[u][i] = nxt[fail[u]][i];
			int v = trie[u].ch[i];
			if (v) {
				fail[v] = nxt[u][i];
				nxt[u][i] = v;
				q.push(v);
			}
		}
	}
}

int tin[N], tout[N], TIME; // Euler tour
vector<int> G[N];
void dfslink(int u) { // dfs in the graph of links
	tin[u] = ++TIME;
	for (int v : G[u]) {
		dfslink(v);
	}
	tout[u] = TIME;
}

void build() {
	bfs();
	for (int i = 1; i < sz; ++i) G[fail[i]].push_back(i);
	dfslink(0);
}

// BIT
int T[N];
void upd(int x, int v) { for (; x < N; x += x & -x) T[x] += v; }
int get(int x) { int ret = 0; for (; x > 0; x -= x & -x) ret += T[x]; return ret; }

// ---------------------------------------------------------
void dfs(int u) { // dfs in trie and find the answers for each node respectively
	upd(tin[u], +1);
	for (int x : all[u]) {
		for (auto e : Q[x]) {
			int id = e.first, y = e.second;
			y = pos[y];
			ans[id] = get(tout[y]) - get(tin[y] - 1);
		}
	}

	for (int i = 0; i < 26; ++i) if (trie[u].ch[i]) {
		dfs(trie[u].ch[i]);
	}
	upd(tin[u], -1);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	string s; cin >> s;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == 'B') {
			cur = trie[cur].par;
		} else if (s[i] == 'P') {
			++n; pos[n] = cur; all[cur].push_back(n);
		} else {
			int c = s[i] - 'a';
			add(c);
		}
	}

	cin >> nquery;
	for (int i = 1; i <= nquery; ++i) {
		int x, y; cin >> y >> x;
		Q[x].push_back(make_pair(i, y)); // (id_query, id_vertex)
	}

	build();
	dfs(0);

	for (int i = 1; i <= nquery; ++i) {
		printf("%d\n", ans[i]);
	}
}