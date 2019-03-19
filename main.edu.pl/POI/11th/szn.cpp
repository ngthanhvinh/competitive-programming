#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

int n;
vector<int> G[N];
int f[N];

int ans;
bool invalid;

void dfs(int u, int p, int val) {
	multiset<int> s;
	vector<int> rem;
	int nChild = 0;
	for (int v : G[u]) if (v != p) {
		dfs(v, u, val);
		s.insert(f[v] + 1);
		++nChild;
	}

	while(!s.empty()) {
		multiset<int>::iterator iter = s.end(); --iter;
		int v = (*iter); s.erase(iter);
		if (v > val) { invalid = true; return; }

		iter = s.upper_bound(val - v);
		if (iter == s.begin()) { rem.push_back(v); continue; }
		--iter;
		s.erase(iter);
		++ans;
	}

	if (rem.size() > 2) { invalid = true; return; }
	if (rem.size() == 2) ++ans;
	if (rem.size()) f[u] = rem[rem.size()-1]; else f[u] = 0;

	if (u == 1) {
		ans += f[u] > 0;
		if (nChild % 2 == 0 && f[u] > 0) invalid = true;
	}
}

bool check(int val) {
	ans = 0;
	invalid = false;
	dfs(1, 1, val);
	return !invalid;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	int l = 0, r = n - 1;
	while(l < r) {
		int mid = ((l + r) >> 1);
		if (check(mid)) r = mid; else l = mid + 1;
	}
	
	check(l);
	printf("%d %d\n", ans, l);
}