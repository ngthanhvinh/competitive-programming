#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1000010;

int n, m, x, a[N];
vector <int> pos[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &x), pos[x].push_back(i);
	int t; cin >> t;
	while(t--) {
		int ans = -1;
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) scanf("%d", &a[i]); 
		if (pos[a[1]].empty()) { printf("NIE\n"); continue; }
		ans = pos[a[1]][0];
		for (int i = 2; i <= m; ++i) {
			int it = upper_bound(pos[a[i]].begin(), pos[a[i]].end(), ans) - pos[a[i]].begin();
			if (it == pos[a[i]].size()) { ans = -1; break; }
			ans = pos[a[i]][it];
		}
		if (ans > 0 && ans <= n) printf("TAK\n");
		else printf("NIE\n");
	}
}