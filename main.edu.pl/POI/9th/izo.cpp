#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n, a[N];
long long sum;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), sum += a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= ((n % 2) ? (n-1) / 2 : (n / 2)); ++i) sum -= a[i];
	for (int i = n; i >= ((n % 2) ? (n-1) / 2 + 2 : (n / 2) + 1); --i) sum += a[i];
	printf("%lld\n", sum);
}