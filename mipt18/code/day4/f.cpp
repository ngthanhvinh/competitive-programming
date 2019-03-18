#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
typedef pair<int,int> ii;
#define x first
#define y second

int n, m, q;
long long f[N + N];
ii pts[N + N];

long long area(vector <ii> &a) {
	long long ret = 0;
	int sz = a.size();
	for (int i = 0; i < sz; ++i) {
		ret += 1LL * (a[i].x + a[(i + 1) % sz].x) * (a[i].y - a[(i + 1) % sz].y);
	}
	return abs(ret);
}

long long pick(vector <ii> a) {
	// s = i + b/2 - 1 <=> 2s = 2i + b - 2
	// i + b = (2s + b + 2) / 2
	long long s = area(a);
	long long b = 0;
	int sz = a.size();
	for (int i = 0; i < sz; ++i) {
		b += __gcd( abs(a[i].x - a[(i + 1) % sz].x), abs(a[i].y - a[(i + 1) % sz].y) );
	}
	return (s + b + 2) / 2;
}

void prepare() {
	for (int i = 1; i <= n - 1; ++i) {
		f[i] = pick({ ii(0, 0), ii(i, m - 1), ii(i - 1, m - 1) }) - __gcd(i - 1, m - 1) - 1;
	}
	for (int i = 0; i <= m - 2; ++i) {
		f[i + n] = pick({ ii(0, 0), ii(n - 1, m - 1 - i), ii(n - 1, m - 2 - i) }) - __gcd(n - 1, m - 1 - i) - 1;
	}
	for (int i = 1; i <= n + m - 2; ++i) {
		f[i] += f[i - 1];
	}
}

int find_region(long long x) {
	int low = 1, high = n + m - 2;
	while(low < high) {
		int mid = ((low + high) >> 1);
		if (f[mid] >= x) high = mid;
		else low = mid + 1;
	}
	return low;
}

bool cmp_frac(ii p, ii q) {
	long long c = 1LL * p.x * q.y - 1LL * p.y * q.x;
	if (c != 0) return c > 0;
	return p.x < q.x || (p.x == q.x && p.y < q.y);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m >> q;

	prepare();

	int c;

	while(q--) {
		long long x; cin >> x;
		if (x < m) {
			printf("1 %lld\n", x + 1); continue;
		}
		if (m == 1) {
			printf("%lld 1\n", x + 1); continue;
		}

		x -= m - 1;
		// [1...n - 1][1...m - 1]
		int region = find_region(x);

		x -= f[region - 1];
		c = 0;

		if (region <= n - 1) {
			if (region == 1) {
				printf("2 %lld\n", m); continue;
			}
			// >= (m - 1) / region, < (m - 1) / (region - 1)
			for (int i = 1; i <= n - 1; ++i) {
				long long low = 1LL * (m - 1) * i / region;
				long long high = (1LL * (m - 1) * i - 1) / (region - 1);
				high = min((long long)m - 1, high);
				low = max(0LL, low);
				if (low > high) continue;
				for (int j = low; j <= high; ++j) {
					pts[c++] = ii(j, i);
				}
			}
		} else {
			region = m + n - 2 - region;
			// >= region / (n - 1), < (region + 1) / (n - 1)
			for (int i = 1; i <= n - 1; ++i) {
				long long low = 1LL * region * i / (n - 1);
				long long high = (1LL * (region + 1) * i - 1) / (n - 1);
				high = min((long long)m - 1, high);
				low = max(0LL, low);
				if (low > high) continue;
				for (int j = low; j <= high; ++j) {
					pts[c++] = ii(j, i);
				}
			}
		}

		nth_element(pts, pts + x - 1, pts + c, cmp_frac);
		printf("%d %d\n", pts[x - 1].y + 1, pts[x - 1].x + 1);
	}
}