#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
const int N = 2005;
const double eps = 1e-12;

struct Point {
	double x; double y; int type;
	Point(double x=0, double y=0, int type=0): x(x), y(y), type(type) {}
	bool operator < (const Point &rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
} a[N], p[N];
int n, m;
int ans;
int color[2];

void rot(double alpha) {
	int cnt[2] = {0,0};
	for (int i = 1; i <= n; ++i) {
		p[i].x = a[i].x * cos(alpha) - a[i].y * sin(alpha);
		p[i].y = a[i].x * sin(alpha) + a[i].y * cos(alpha);
		p[i].type = a[i].type;
	}
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; ) {
		double X = p[i].x;
		while(i <= n && fabs(X - p[i].x) <= eps) {
			cnt[p[i].type]++;
			++i;
		}
		ans = max(ans, cnt[0] + color[1] - cnt[1]);
		ans = max(ans, cnt[1] + color[0] - cnt[0]);
	}
}

void solve() {
	ans = 0;
	color[0] = color[1] = 0;

	cin >> n >> m;
	for (int i = 1; i <= n+m; ++i) {
		cin >> a[i].x >> a[i].y;
		if (i <= n) a[i].type = 0; else a[i].type = 1;
		color[a[i].type]++;
	}
	n += m;
	double C = pi / 1000;
	for (int i = -1000; i <= 1000; ++i) {
		double alpha = C * i;
		rot(alpha);
	}
	cout << n - ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	while(tt--) {
		solve();
	}
}