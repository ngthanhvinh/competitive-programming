#include <bits/stdc++.h>
using namespace std;

struct Point {
	double x; double y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	Point operator + (const Point &other) const {
		return Point(x + other.x, y + other.y);
	}
	Point operator - (const Point &other) const {
		return Point(x - other.x, y - other.y);
	}
};
double cross(Point p, Point q) {
	return p.x * q.y - q.x * p.y;
}
double dist(Point p, Point q) {
	return hypot(p.x - q.x, p.y - q.y);
}

struct Line {
	Point a, ab; // a + i * (vector)ab
	Line(Point p = Point(), Point q = Point()): a(p), ab(q - p) {} // segment (p,q)
};

Point find_inter(Line p, Line q, bool &valid) {
	// find the intersection of ray (A, B) with segment (C, D)
	auto a = p.a, c = q.a;
	auto ab = p.ab, cd = q.ab;

	double t = cross(ab, cd);
	if (t == 0) { // parallel
		valid = false; return Point();
	}
	double i = (double)cross(c - a, cd) / t;
	if (i < 1) { // the intersection does not lie on (C, D)
		valid = false; return Point();
	}

	Point w = Point(a.x + i * ab.x, a.y + i * ab.y);
	if ((w.x > q.a.x && w.x > (q.a.x + q.ab.x)) || (w.x < q.a.x && w.x < (q.a.x + q.ab.x))) {
		valid = false; return Point();
	}
	if ((w.y > q.a.y && w.y > (q.a.y + q.ab.y)) || (w.y < q.a.y && w.y < (q.a.y + q.ab.y))) {
		valid = false; return Point();
	}

	valid = true;
	return w;
}
// ----------------------------------------------------

const int N = 205;
const double INF = 1e12;

int n, m;
Point a[N], b[N];
double f[N][N];
Point inter[N][2];

void change(Point &w, Line p, Line c, Line d) { 
	// ray p, segment c, segment d
	bool valid = false;
	Point e;

	// (p, c)
	e = find_inter(p, c, valid);
	if (valid) {
		w = e; return;
	}

	// (p, d)
	e = find_inter(p, d, valid);
	if (valid) {
		w = e; return;
	}
}

double dp(int l, int r) { // l -> r (clockwise)
	if (l == r) return 0.0;
	if (f[l][r] != 0) return f[l][r];

	Point inter_l = inter[(l + m - 1) % m][0]; // b[l - 1] -> b[l]
	Point inter_r = inter[(r + 1) % m][1]; // b[r + 1] -> b[r]
	double &ret = f[l][r];

	ret = INF;
	for (int k = l; k != r; k = (k + 1) % m) {
		Point w1 = inter[k][0];
		Point w2 = inter[(k + 1) % m][1];

		change(w1, Line(b[k], b[(k + 1) % m]), Line(b[l], inter_l), Line(b[r], inter_r));
		change(w2, Line(b[(k + 1) % m], b[k]), Line(b[l], inter_l), Line(b[r], inter_r));

		ret = min(ret, dp(l, k) + dp((k + 1) % m, r) + dist(w1, w2));
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n; // A
	for (int i = 0; i < n; ++i) {
		cin >> a[i].x >> a[i].y;
	}
	cin >> m; // B
	for (int i = 0; i < m; ++i) {
		cin >> b[i].x >> b[i].y;
	}

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			bool valid = false;
			Point w;
			// ray: b[i] -> b[i + 1]
			w = find_inter(Line(b[i], b[(i + 1) % m]), Line(a[j], a[(j + 1) % n]), valid);
			if (valid) inter[i][0] = w;
			// ray: b[i] -> b[i - 1]
			valid = false;
			w = find_inter(Line(b[i], b[(i + m - 1) % m]), Line(a[j], a[(j + 1) % n]), valid);
			if (valid) inter[i][1] = w;
		}
		//printf("ray b[%d] -> b[%d]: intersection: [%.6lf %.6lf]\n", i, (i + 1) % m, inter[i][0].x, inter[i][0].y);
		//printf("ray b[%d] -> b[%d]: intersection: [%.6lf %.6lf]\n", i, (i + m - 1) % m, inter[i][1].x, inter[i][1].y);
	}
	// each ray intersects with only one edge of the polygon

	// dp
	double res = INF;
	for (int i = 0; i < m; ++i) {
		int j = (i + 1) % m;
		res = min(res, dist(inter[i][0], inter[j][1]) + dp(j, i));
	}

	cout << setprecision(6) << fixed << res << endl;
}