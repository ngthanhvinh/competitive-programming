#include <bits/stdc++.h>
using namespace std;

int n, k;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	if (n & 1) {
		if (k > (n - 1) / 2) return printf("NIE\n"), 0;
		for (int i = 1; i <= n; i += 2) {
			printf("%d ", i / 2 + 1);
			if (i != n) printf("%d ", (n - 1) / 2 + 2 + (i / 2));
		}
		printf("\n");
	} else {
		if (k > n / 2) return printf("NIE\n"), 0;
		for (int i = 1; i <= n; i += 2) {
			printf("%d ", (i / 2) + 1 + (n / 2));
			printf("%d ", (i / 2) + 1);
		}
		printf("\n");
	}
}