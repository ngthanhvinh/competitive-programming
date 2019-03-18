#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-6;

int myfloor(long double d) {
	int x = (int)d;
	if (abs(x + 1 - d) <= EPS) ++x;
	if (abs(x - 1 - d) <= EPS) --x;
	return x;
}

int main() {
	ios_base::sync_with_stdio(false);
	int a, b, c;
	cin >> a >> b >> c;

	long long x = (1LL * a * b) / c;
	int z = (1LL * a * b) % c;
	long double d = (long double) z / c;

	int y = 0; // real part
	for (int i = 0; i < 6; ++i) {
		d *= 10.0;
		z = myfloor(d);
		y = 10 * y + z;
		d -= z;
	}

	printf("%lld.%06d\n", x, y);
}