#include <bits/stdc++.h>
using namespace std;

const int N = 555;

int nchar, len, nforbid;
map <char, int> mchar;
int nxt[N][55];
int fail[N];

struct Node {
	int ch[55];
	bool is;
	Node() {
		memset(ch, 0, sizeof ch);
		is = 0;
	}
} trie[N]; // root = 0
int sz;

void add(string &s) {
	int cur = 0;
	for (int i = 0; i < s.size(); ++i) {
		int c = mchar[s[i]];
		if (trie[cur].ch[c] == 0) {
			trie[cur].ch[c] = ++sz;
		}
		cur = trie[cur].ch[c];
	}
	trie[cur].is = true;
}

void bfs() {
	queue <int> q;
	q.push(0);

	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int c = 1; c <= nchar; ++c) {
			nxt[u][c] = nxt[fail[u]][c];
			if (trie[u].ch[c]) {
				int v = trie[u].ch[c];
				fail[v] = nxt[u][c];
				nxt[u][c] = v;
				q.push(v);
			}
		}
	}
}

struct BigInt {
	vector <int> a;
	static const int BASE = 100000; // 10^5

	BigInt(int x = 0) { // x < BASE
		a.assign(1, x);
	}

	void fix() {
		a.push_back(0);
		for (int i = 0; i < (int)a.size() - 1; ++i) {
			a[i + 1] += a[i] / BASE; a[i] %= BASE;
			if (a[i] < 0) a[i + 1]--, a[i] += BASE;
		}
		while(a.size() >= 2 && a.back() == 0) a.pop_back();
	}

	void operator += (BigInt v) {
		a.resize(max(a.size(), v.a.size()));
		for (int i = 0; i < v.a.size(); ++i) {
			a[i] += v.a[i];
		}
		fix();
	}

	void out() {
		printf("%d", a.back());
		for (int i = (int)a.size() - 2; i >= 0; --i) {
			printf("%05d", a[i]);
		}
		printf("\n");
	}
} dp[55][N];

bool check(int u) {
	while(u && !trie[u].is) {
		u = fail[u];
	}
	if (!u) return true;
	else return false;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	// cout << 50 << ' ' << 50 << ' ' << 0 << endl;
	// for (int i = 0; i < 25; ++i) {
	// 	cout << (char)(i + 'a') << ' ' << (char)(i + 'A') << ' ';
	// }
	// cout << endl;

	cin >> nchar >> len >> nforbid;
	
	for (int i = 1; i <= nchar; ++i) {
		char c; cin >> c; mchar[c] = i; // alphabet
	}

	for (int i = 0; i < nforbid; ++i) {
		string s; cin >> s;
		add(s);
	}
	bfs();

	dp[0][0] = BigInt(1);
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j <= sz; ++j) {
			for (int k = 1; k <= nchar; ++k) {
				int to = nxt[j][k];
				if (to != 0 && !check(to)) continue;
				dp[i + 1][to] += dp[i][j];
			}
		}
	}

	// find result
	BigInt res = BigInt(0);
	for (int j = 0; j <= sz; ++j) {
		res += dp[len][j];
	}
	res.out();
}