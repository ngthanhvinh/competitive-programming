#include <bits/stdc++.h>
using namespace std;

double ans1, ans2;
int n, m, a[100005], s;

double pw(double a, int n) {
	double ret = 1.0;
	while(n) {
		if (n & 1) ret *= a; a *= a;
		n >>= 1;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i], s += a[i];

	long long m2 = 1LL * m * (m - 1);

	for (int i = 1; i <= n; ++i) {
		double p = 1.0 * a[i] / s;
		ans2 += 1.0 - pw(1.0 - p, m);
		ans1 += p * m + p * p * m2;
	}

	cout << setprecision(2) << fixed;
	cout << ans1 << endl << ans2 << endl;
}