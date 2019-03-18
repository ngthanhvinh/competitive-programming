#include <bits/stdc++.h>
using namespace std;

const int N = 3010;
const double eps = 1e-12;
const double pi = acos(-1);

int n, D;
int ans;

struct Point {
	double x; double y;
	Point(double x=0, double y=0): x(x), y(y) {}
} a[N];

double dist(Point p, Point q) {	return hypot(p.x - q.x, p.y - q.y); }
double cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }
bool eq(double x, double y) { return abs(x-y) <= eps; }

double angle(Point p) {
	double res = atan2(p.y, p.x);
	return res < 0 ? res + 2 * pi : res;
}

int calc(Point pivot) {
	int res = 0;
	int has = 0;
	vector<Point> vec;
	for (int i = 1; i <= n; ++i) {
		a[i].x -= pivot.x, a[i].y -= pivot.y;
		if (!eq(a[i].x, 0) || !eq(a[i].y, 0)) vec.push_back(a[i]);
		else ++has;
	}

	sort(vec.begin(), vec.end(), [&](Point p, Point q) {
		return angle(p) < angle(q);
	});

	int cnt = 0;
	Point lst;
	for (int i = 0; i < vec.size(); ++i) {
		++cnt;
		if (i > 0 && !eq(angle(lst), angle(vec[i]))) cnt = 1;
		res = max(res, cnt + has);
		lst = vec[i];
	}

	for (int i = 1; i <= n; ++i) a[i].x += pivot.x, a[i].y += pivot.y;
	return res;
}

void solve() {
	cin >> a[0].x >> a[0].y;
	cin >> D >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].x >> a[i].y;
		a[i].x -= a[0].x; a[i].y -= a[0].y;
	} 

	vector<Point> vec;
	for (int i = 1; i <= n; ++i) if (dist(a[i], {0,0}) <= D) vec.push_back(a[i]);

	sort(vec.begin(), vec.end(), [&](Point p, Point q) {
		return angle(p) < angle(q);
	});
	
	ans = 0;
	int cnt = 0;
	Point lst;
	for (int i = 0; i < vec.size(); ++i) {
		++cnt;
		if (i > 0 && !eq(angle(lst), angle(vec[i]))) cnt = 1;
		lst = vec[i];

		double d = dist(vec[i], {0,0});
		Point pivot = Point(vec[i].x / d * D, vec[i].y / d * D);
		ans = max(ans, cnt * calc(pivot));
	}

	printf("%d\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}