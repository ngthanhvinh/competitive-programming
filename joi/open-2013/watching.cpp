#include <bits/stdc++.h>
using namespace std;
 
const int N = 2005;
 
int n, p, q;
long long a[N];
int to1[N], to2[N];
int f[N][N];
 
bool check(int w) {
	int pt = 1;
	for (int i = 1; i <= n; ++i) {
		while(pt <= n && a[i] + w - 1 >= a[pt]) ++pt; --pt;
		to1[i] = pt;
	}
	pt = 1;
	for (int i = 1; i <= n; ++i) {
		while(pt <= n && a[i] + 2LL * w - 1 >= a[pt]) ++pt; --pt;
		to2[i] = pt;
	}
 
	for (int i = 0; i <= p; ++i) {
		for (int j = 0; j <= q; ++j) {
			f[i][j] = 0;
			if (i > 0) f[i][j] = max(f[i][j], to1[f[i-1][j] + 1]);
			if (j > 0) f[i][j] = max(f[i][j], to2[f[i][j-1] + 1]);
 
			if (f[i][j] >= n) return true;
		}
	}
 
	return false;
}
 
int main() {
	scanf("%d %d %d", &n, &p, &q);
	if (p >= n || q >= n) {
		return printf("1\n"), 0;
	}
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	
	int l = 1, r = 1e9;
	while(l < r) {
		int mid = ((l + r) >> 1);
		if (check(mid)) r = mid; else l = mid + 1;
	}
	printf("%d\n", l);
}