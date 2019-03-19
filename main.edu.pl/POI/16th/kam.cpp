#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1010;

int n, a[N];

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		scanf("%d", &n); for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		reverse(a + 1, a + n + 1); a[n+1] = 0;
		int ans = 0;
		for (int i = 1; i <= n; ++i) { int x = a[i] - a[i+1]; if (i & 1) ans ^= x; }
		if (ans > 0) printf("TAK\n");
		else printf("NIE\n");
	}
}