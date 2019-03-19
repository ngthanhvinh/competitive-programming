#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

int n, a[N], t[N];
vector <int> G[N];

void upd(int x) { for (; x <= n; x += x & -x) t[x]++; }
int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }

typedef pair<int,int> ii;
vector <ii> vec;

int sz[N];
void dfs(int u) {
	sz[u] = 1;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (!a[v] && a[u]) vec.push_back(ii(a[u], v));
		dfs(v);
		sz[u] += sz[v];
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	int r = 0;
	for (int i = 1; i <= n; ++i) {
		int p; cin >> p >> a[i];
		if (p == i) r = i;
		else G[p].push_back(i);
	}
	for (int i = 1; i <= n; ++i) if (a[i]) upd(a[i]);
	dfs(r);
	sort(vec.begin(), vec.end(), greater<ii>());

	while(!vec.empty()) {
		int val = vec.back().first, u = vec.back().second; vec.pop_back();
		cerr << val << ' ' << u << ' ' << sz[u] << endl;
		if (val - 1 - get(val - 1) == sz[u]) {
			a[u] = val - 1; upd(val - 1);
			for (int i = 0; i < G[u].size(); ++i) vec.push_back(ii(a[u], G[u][i]));
		}
	}

	for (int i = 1; i <= n; ++i) printf("%d\n", a[i]);
}