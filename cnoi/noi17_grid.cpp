#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
map <ii, bool> mp;

bool id(int x, int y) {
	if (x == 0 || y == 0 || x == n + 1 || y == m + 1) return c + 1;
	if (mp.count(ii(x, y))) return mp[ii(x, y)];
	return 0;
}

int ncomp() {
	mp.clear();
	for (int i = 1; i <= c; ++i) par[i] = i, mp[a[i]] = i;
	sort(a, a + n);
	
	// planar graph: E - V + F = 1
	int ret = 0;
	int nedge = 0;

	for (int i = 1; i <= c; ++i) {
		int u = a[i].first, v = a[i].second;

		if (id(u - 1, v)) join(i, id(u - 1, v)]);
		if (id(u, v - 1)) join(i, id(u, v - 1)]);
	}	

	for (int i = 1; i <= c; ++i) {
		int u = a[i].first, v = a[i].second;

		
	}
}

bool find() {

}

void prepare() {
	
}

void solve() {
	scanf("%d%d%d", &n, &m, &c);
	if (c == 0) {
		if (1LL * n * m <= 2) { printf("-1\n"); return; }
		printf("%d\n", 1 + (n > 1 && m > 1));
	} else {
		for (int i = 1; i <= c; ++i) scanf("%d%d", &a[i].first, &a[i].second);
		if (ncomp() > 1) { printf("0\n"); continue; }

		if (1LL * n * m - c <= 2) printf("-1\n");
		else {
			if (find()) printf("1\n");
			else printf("2\n");
		}
	}
}

int main() {
	scanf("%d", &tt);
	while(tt--) {
		solve();
	}
}