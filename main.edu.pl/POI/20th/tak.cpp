#include <bits/stdc++.h>
using namespace std;

long long d, m;
int n;
long long a[500010];

int solve() {
	int x = 0;
	for (int i = n; i >= 1; --i) if (a[i] >= m - d) { x = i; break; }
	long long dist = a[x];
	while(x + 1 <= n) a[x] = a[x + 1], ++x; --n; a[n + 1] = 0;

	long long cur = 0;
	for (int i = 1; i <= n + 1; ++i) {
		if (2 * (d - cur) + m - d <= dist) return i;
		if (a[i] <= d - cur) return 0;
		cur += (a[i] - d + cur);
		if (cur >= m) return i;
	}

	return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> m >> d >> n; for (int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1, greater <long long> ());
	cout << solve() << endl;
	
}