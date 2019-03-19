#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> Point;
#define x first
#define y second
const int N = 605;

int n, k, mod;
Point a[N], b[20005];
bool e[N][N];
int f[N][N];

long long cross(Point O, Point A, Point B) {
	A.x -= O.x; A.y -= O.y;
	B.x -= O.x; B.y -= O.y;
	return 1LL * A.x * B.y - 1LL * A.y * B.x;
}

int main() {
	scanf("%d %d %d", &n, &k, &mod);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &a[i].x, &a[i].y);
	}
	reverse(a, a + n);
	for (int i = 0; i < k; ++i) {
		scanf("%d %d", &b[i].x, &b[i].y);
	}

	for (int i = 0; i < n; ++i) {
		sort(b, b + k, [&](Point p, Point q) {
			return cross(a[i], p, q) > 0;
		});
		int pt = 0, cnt = 0;
		for (int j = (i+1) % n; j != i; j = (j+1) % n) {
			while(pt < k && cross(a[i], b[pt], a[j]) > 0) ++pt, ++cnt;
			if (pt < k && cross(a[i], b[pt], a[j]) == 0) continue;
			if (cnt % 2 == 0) {
				e[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < n-1; ++i) f[i][i+1] = 1;
	for (int gap = 2; gap < n; ++gap) {
		for (int i = 0; i + gap < n; ++i) {
			if (!e[i][(i + gap) % n]) {
				f[i][(i + gap) % n] = 0;
				continue;
			}
			for (int j = i+1; j < i + gap; ++j) {
				f[i][(i + gap) % n] += 1LL * f[i][j] * f[j][(i + gap) % n] % mod;
				f[i][(i + gap) % n] %= mod;
			}
		}
	}

	int ans = 0;
	for (int i = 1; i < n-1; ++i) {
		if (e[0][i] && e[i][n-1]) {
			ans += 1LL * f[0][i] * f[i][n-1] % mod;
			ans %= mod;
		}
	}
	printf("%d\n", ans);
}