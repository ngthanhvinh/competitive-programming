#include <bits/stdc++.h>
using namespace std;

const int md = 1e9 + 7, mxn = 1e6;

long long N;
int C;
map <long long, int> f;
int g[mxn+5];

int F(long long n) {
	if (n <= mxn) return g[n];
	if (f.count(n)) return f[n];

	int ret = 0;

	if (f.count(n - 1) && f.count(n - C - 2)) {
		ret = 2LL * F(n - 1) % md;
		ret = (ret - F(n - C - 2)) % md;
		if (ret < 0) ret += md;
		return f[n] = ret;
	}

	long long k = n / 2;
	int s = 0, d = n % 2;
	vector<int> a;
	for (int i = C + 1; i >= 0; --i) a.push_back(F(k - i));
	for (int i = d; i <= C + d; ++i) s = (s + a[i]) % md;

	for (int i = C; i >= 0; --i) {
        ret = (ret + 1LL * a[i] * s) % md;
        s = (s + md - a[C+d-i]) % md;
	}

	return f[n] = ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> N >> C;
	//N = 1e18, C = 200;
	g[0] = 1;
	for (int i = 1; i <= C + 1; ++i) g[i] = 2 * g[i-1] % md;
	--g[C+1];
	for (int i = C + 2; i <= mxn; ++i) g[i] = (2LL * g[i-1] + md - g[i-C-2]) % md;
	cout << F(N) << endl;
}