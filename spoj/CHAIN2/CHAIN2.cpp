#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 26;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

struct node {
	node* child[N]; int f; bool end;
	node() { fo(i, 0, N) child[i] = NULL; f = end = 0; }
	~node() { fo(i, 0, N) delete child[i]; }
} *Trie = new node();

void add(string s) {
	node* cur = Trie;
	fo(i, 0, s.size()) {
		if (cur -> child[s[i] - 'a'] == NULL) cur -> child[s[i] - 'a'] = new node();
		cur = cur -> child[s[i] - 'a'];
	}
	cur -> end = 1;
}

void dfs(node* u) {
	int Max = 0;
	fo(i, 0, N) {
		node* v = u -> child[i];
		if (v != NULL) {
			dfs(v); Max = max(Max, v -> f);
		}
	}
	u -> f = max(Max + (u -> end), u -> f); 
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n; 
	ff(i, 1, n) { string s; cin >> s; add(s); }
	dfs(Trie);
	printf("%d\n", Trie -> f);
}