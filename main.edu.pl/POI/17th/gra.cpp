#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000010;
const long long INF = 1e18;

int n, a[N];
long long f[N][2];
long long mn0, mx1;

int main() {
	scanf("%d", &n); for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	mx1 = a[1], mn0 = -a[1];
	for (int i = 1; i <= n; ++i) {
		f[i][0] = mx1, f[i][1] = mn0;
		mx1 = max(mx1, f[i][1] + a[i+1]);
		mn0 = min(mn0, f[i][0] - a[i+1]);
	}
	printf("%lld\n", f[n][0]);
}