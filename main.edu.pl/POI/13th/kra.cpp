#include <bits/stdc++.h>
using namespace std;

const int N = 300005;
const int inf = 1e9 + 123;

int n, k, a[N];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	a[0] = inf;
	for (int i = 1; i <= n; ++i) a[i] = min(a[i], a[i-1]);
	++n;

	while(k--) {
		int x; scanf("%d", &x);
		if (a[n] >= x) { --n; continue; }
		while(n > 0) {
			if (a[n] < x) --n;
			else break;
		}
	}
	printf("%d\n", max(0,n));
}