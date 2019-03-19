#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;

int n;
long long a[N];
long long ans;
bool check[N];

int main() {
	scanf("%d", &n); for (int i = 1; i <= n; ++i) scanf("%lld", a+i);
	if (n == 1) return printf("%lld\n", a[1]), 0;
	ans = a[2];
	for (int i = n-1; i >= 3; --i) if (!check[i] && !check[i+1] && a[i] >= 2 * a[2] - a[1]) ans += 2 * a[2] - a[1] - a[i], check[i] = check[i+1] = 1; 
	for (int i = 3; i <= n; ++i) ans += a[1] + a[i];
	printf("%lld\n", ans);
}