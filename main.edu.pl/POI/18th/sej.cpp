#include <bits/stdc++.h>
using namespace std;

const int N = 250005;

int k;
long long n, m, a[N];
vector<long long> dvs;
int check[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i < k; ++i) cin >> a[i];
	cin >> m;
	m = __gcd(m, n);

	for (int i = 1; 1LL * i * i <= m; ++i) {
		if (m % i == 0) {
			dvs.push_back(i);
			if (m != 1LL * i * i) dvs.push_back(m / i);
		}
	}
	sort(dvs.begin(), dvs.end());

	for (int i = 1; i < k; ++i) {
		a[i] = __gcd(a[i], m);
		int di = lower_bound(dvs.begin(), dvs.end(), a[i]) - dvs.begin();
		if (check[di]) continue;
		for (int j = 0; j <= di; ++j) {
			if (dvs[di] % dvs[j] == 0) check[j] = 1;
		}
	}

	for (int i = 0; i < dvs.size(); ++i) {
		if (!check[i]) {
			printf("%lld\n", n / dvs[i]);
			return 0;
		}
	}

	printf("0\n");
}