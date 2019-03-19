#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

const int N = 300010;

int n, d[N];
vector<int> G[N];
vector<int> vec;

void dfs(int u, int p) {
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i]; if (v == p) continue;
		d[v] = d[u] + 1; vec.push_back(d[v]); dfs(v, u);
	}
}

bool check(int x) {
	vector<int> nodes = vec;
	for (int i = 0; i < nodes.size(); ++i) cerr << nodes[i] << ' '; cerr << endl;
	int days = 0;
	while(!nodes.empty()) {
		int u = nodes.back(); nodes.pop_back();
		cerr << u << ' ' << days << endl;
		if (days % x == 0 && u <= days / x) return 0;
		++days;
	}
}

int main() {	
	scanf("%d", &n);
	if (n == 1) return printf("0\n"), 0;
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	dfs(1, 1);
	sort(vec.begin(), vec.end(), greater<int>());
	/*
	int l = 1, r = n;
	while(l != r) {
		int mid = ((l + r) >> 1);
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	*/
	cout << check(3) << endl;
}