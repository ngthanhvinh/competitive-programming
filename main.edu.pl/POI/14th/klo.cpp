#include <bits/stdc++.h>
using namespace std;
// note: a[i] > a[j] && i - a[i] >= j - a[j] <=> i > j

const int N = 1e5 + 5;

int n, a[N];
int f[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) if (a[i] > a[j] && i - a[i] >= j - a[j]) {
			f[i] = max(f[i], f[j] + 1);
		}
	}
}