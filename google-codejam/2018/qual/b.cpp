#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, a[N];

void read(int &x) { // x >= 0
	x = 0;
	char c = getchar();
	while(c < 48 || c > 57) c = getchar();
	for (; c >= 48 && c <= 57; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
}

void solve() {
	read(n);
	for (int i = 1; i <= n; ++i) read(a[i]);

	vector <int> odd, even;
	for (int i = 1; i <= n; i += 2) odd.push_back(a[i]);
	for (int i = 2; i <= n; i += 2) even.push_back(a[i]);

	sort(odd.begin(), odd.end());
	sort(even.begin(), even.end());

	for (int i = 0, j = 1; j <= n; j += 2, ++i) {
		a[j] = odd[i];
	}
	for (int i = 0, j = 2; j <= n; j += 2, ++i) {
		a[j] = even[i];
	}

	for (int i = 1; i < n; ++i) {
		if (a[i] > a[i + 1]) { printf("%d\n", i - 1); return; }
	}

	printf("OK\n");
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int tt; read(tt);
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}