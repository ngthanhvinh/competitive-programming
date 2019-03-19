#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n;
int in[N];
bool win[N];
vector<int> G[N];

bool found(int u, int v) {
	int pos = lower_bound(G[u].begin(), G[u].end(), v) - G[u].begin();
	if (pos == G[u].size()) return false;
	return G[u][pos] == v;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int sz; cin >> sz;
		while(sz-- > 0) { int u; cin >> u; G[i].push_back(u); ++in[u]; } 
	}
	for (int i = 1; i <= n; ++i) {
		sort(G[i].begin(), G[i].end());
	}
	int rt = 1;
	for (int i = 1; i <= n; ++i) if (in[i] < in[rt]) rt = i;
	
	set <int> s; 
	for (int i = 1; i <= n; ++i) if (i != rt) s.insert(i);

	queue <int> q;
	q.push(rt);

	while(!q.empty()) {
		int u = q.front(); q.pop(); win[u] = 1;
		vector<int> del;
		for (set<int>::iterator iter = s.begin(); iter != s.end(); ++iter) {
			int v = (*iter);
			if (!found(u, v)) del.push_back(v), q.push(v);
		}
		for (int v : del) s.erase(v);
	}

	vector<int> ans;
	for (int i = 1; i <= n; ++i) if (win[i]) ans.push_back(i);
	printf("%d ", ans.size()); for (int u : ans) printf("%d ", u); printf("\n");
}