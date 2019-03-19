#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, s, a[N];
long long f[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> s;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 2; i <= n; ++i) {
		if (a[i] <= a[i-1]) a[i] = a[i-1] + 1;
	}

	int j = 0;
	for (int i = 1; i <= n; ++i) {
		while(j <= i-1 && f[j] - j - 1 <= a[i] - i) ++j; --j;
		f[i] = 2LL * s + a[i] + i - j - 1;
		if (j < i-1) f[i] = min(f[i], f[j+1] - (j+1) * 2 + i * 2 + 2LL * s - 2);
	}

	cout << f[n] << endl;
}