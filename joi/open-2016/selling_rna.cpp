#include <bits/stdc++.h>
using namespace std;

int id(char c) {
	if (c == 'A') return 0;
	else if (c == 'G') return 1;
	else if (c == 'C') return 2;
	else return 3;
}

const int N = 100010;
typedef pair<int,int> ii;

int TIME;
struct Trie {
	struct Node {
		int ch[4]; int f;
		Node() { memset(ch, -1, sizeof ch); f = 0; }
	};
	vector<Node> tr;
	vector<int> tin, tout;
	void init() { tr.clear(); tin.clear(); tout.clear(); tr.push_back(Node()); }

	void add(string &s) {
		int cur = 0;
		for (int i = 0; i < s.size(); ++i) {
			int ID = id(s[i]);
			if (tr[cur].ch[ID] == -1) {
				tr[cur].ch[ID] = tr.size(), tr.push_back(Node());
			}
			cur = tr[cur].ch[ID];
			tr[cur].f++;
		}
	} 

	void dfs(int u) {
		tin[u] = ++TIME;
		for (int i = 0; i < 4; ++i) if (tr[u].ch[i] != -1) dfs(tr[u].ch[i]);
		tout[u] = TIME;
	}

	void prepare() {
		tin.assign(tr.size(), 0); tout.assign(tr.size(), 0); dfs(0);
	}

	ii get_pos(string &s) {
		int cur = 0;
		for (int i = 0; i < s.size(); ++i) {
			int ID = id(s[i]);
			if (tr[cur].ch[ID] == -1) return ii(-1,-1);
			cur = tr[cur].ch[ID];
		}
		return ii(tin[cur], tout[cur]);
	}

	int query(string &s) {
		int cur = 0;
		for (int i = 0; i < s.size(); ++i) {
			int ID = id(s[i]);
			if (tr[cur].ch[ID] == -1) return 0;
			cur = tr[cur].ch[ID];
		}
		return tr[cur].f;
	}
} it[N << 2], pref;

int n, m;
vector<ii> vec;
string s[N];

#define mid ((l + r) >> 1)
void build(int v, int l, int r) {
	it[v].init();
	for (int i = l; i <= r; ++i) it[v].add(s[vec[i].second]);
	if (l == r) return;
	build(v << 1, l, mid); build(v << 1 | 1, mid + 1, r);
}

int get(int v, int l, int r, int L, int R, string &s) {
	if (l > r || R < l || L > r) return 0;
	if (L <= l && r <= R) return it[v].query(s);
	return get(v << 1, l, mid, L, R, s) + get(v << 1 | 1, mid + 1, r, L, R, s);
}
#undef mid

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	pref.init();
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		pref.add(s[i]);
	}
	pref.prepare();
	
	for (int i = 1; i <= n; ++i) {
		int pos = pref.get_pos(s[i]).first;
		vec.push_back(ii(pos, i));
	}
	sort(vec.begin(), vec.end());

	for (int i = 1; i <= n; ++i) reverse(s[i].begin(), s[i].end());
	build(1, 0, n - 1);
	
	string p, q;
	while(m--) {
		cin >> p >> q;
		ii P = pref.get_pos(p);
		if (P.first == -1 && P.second == -1) {
			printf("0\n"); continue;
		}
		reverse(q.begin(), q.end());
		P.first = lower_bound(vec.begin(), vec.end(), ii(P.first, 0)) - vec.begin();
		P.second = upper_bound(vec.begin(), vec.end(), ii(P.second, 1e9)) - vec.begin() - 1;
		int res = get(1, 0, n - 1, P.first, P.second, q);
		printf("%d\n", res);
	}
}