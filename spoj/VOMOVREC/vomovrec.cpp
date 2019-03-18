#include <bits/stdc++.h>
using namespace std;

typedef pair <long long, long long> pt;
typedef pair <pt, pt> rec;
#define x first
#define y second

int n;
vector <rec> a;

bool f(long long val) {
	long long X1 = -1e18, X2 = 1e18, Y1 = -1e18, Y2 = 1e18;
	for (int i = 1; i <= n; i++) {
		long long nX1 = a[i].x.x - val; X1 = max(X1, nX1);
		long long nY1 = a[i].x.y - val; Y1 = max(Y1, nY1);
		long long nX2 = a[i].y.x + val; X2 = min(X2, nX2);
		long long nY2 = a[i].y.y + val; Y2 = min(Y2, nY2);
	}
	if (X1 < X2 && Y1 < Y2) return 1; return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; a.assign(n + 1, rec());
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x.x >> a[i].x.y >> a[i].y.x >> a[i].y.y;
	} 
	long long l = 0, r = 5LL * 1e9;
	while(l != r) {
		long long mid = ((l + r) >> 1);
		if (f(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
}