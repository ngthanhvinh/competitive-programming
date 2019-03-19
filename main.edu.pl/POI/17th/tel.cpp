#include <bits/stdc++.h>
using namespace std;

const int N = 40005;

int n, m;
int d1[N], d2[N];
vector<int> G[N];
long long ans;
vector<int> a, b, c;
int type[N];

void bfs(int s, int d[]) {
	for (int i = 1; i <= n; ++i) d[i] = -1;
	d[s] = 0;
	for (int v : G[s]) d[v] = 1;
} 

int main() {
	scanf("%d %d", &n, &m);
	while(m--) {
		int u, v; scanf("%d %d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	bfs(1, d1);
	bfs(2, d2);

	for (int i = 3; i <= n; ++i) {
		if (d1[i] == 1) a.push_back(i), type[i] = 1;
		else if (d2[i] == 1) b.push_back(i), type[i] = 2;
		else c.push_back(i), type[i] = 3;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j : G[i]) if (j > i && type[i] == type[j]) --ans;
	}
	ans += 1LL * a.size() * (a.size() - 1) / 2;
	ans += 1LL * b.size() * (b.size() - 1) / 2;
	ans += 1LL * c.size() * (c.size() - 1) / 2;

	for (int u : c) {
		int adjA = 0, adjB = 0;
		for (int v : G[u]) {
			if (d1[v] == 1) ++adjA;
			if (d2[v] == 1) ++adjB;
		}
		if (adjA == 0 && adjB == 0) {
			ans += max((int)a.size(), (int)b.size());
		} else if (adjA == 0) {
			ans += b.size() - adjB;
		} else if (adjB == 0) {
			ans += a.size() - adjA;
		}

		if (a.size() == 0 && b.size() == 0) ++ans;
	}

	printf("%lld\n", ans);
}