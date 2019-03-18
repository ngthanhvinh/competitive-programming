#include <bits/stdc++.h>
using namespace std;

const int md = 1e9 + 7;
const int N = 4010;

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; ++i) {
		if (b & (1LL << i)) res = 1LL * res * a % md;
		a = 1LL * a * a % md;
	}
	return res;
}

int C[N][N];
int f[N][N];
void prep() {
	for (int i = 0; i < N; ++i) C[i][0] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= i; ++j) C[i][j] = (C[i-1][j] + C[i-1][j-1]) % md;
	}
	f[1][0] = 1;
	for (int i = 1; i < N - 1; ++i) for (int j = 0; j < i; ++j) {
		if (i > j + 1) f[i][j + 1] = (f[i][j + 1] + f[i][j]) % md;
		f[i + 1][j] = (f[i + 1][j] + f[i][j]) % md;
	}
}

void solve() {
	int a, b;
	scanf("%d-%d", &a, &b);
	printf("%d ", f[a][b]);
	printf("%d\n", 1LL * pw(b + 1, md - 2) * C[2 * b][b] % md);
}

int main() {
	prep();
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}