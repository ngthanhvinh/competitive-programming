#include <bits/stdc++.h>
using namespace std;
 
const int N = 1010;
const int MAX = 100005;
const double eps = 1e-12;
 
long long cnt[MAX + MAX];
int n, m;
 
struct Point { 
	int x; int y; 
	Point(int x = 0, int y = 0): x(x), y(y) {}
} a[N];
 
struct Line {
	bool pX; // is this line parallel with Ox?
	long long a; long long b; long long c; // ax + by + c = 0
	Line() {}
	Line(Point p, Point q) {
		pX = false;
		if (p.x == q.x) {
			a = 1; b = 0; c = -p.x; pX = true; return;
		}
		a = p.y - q.y;
		b = q.x - p.x;
		c = 1LL * p.x * q.y - 1LL * q.x * p.y;
	}
	bool intersect(double alpha, double &x, double &inter) { 
		// find the intersection of this line and the line y = alpha
		if (a == 0) return false;
		inter = ((double)-b * alpha - c) / a;
		if (pX) x = alpha; else x = inter;
		return true;
	}
};
 
struct Segment {
	Line l; int mn; int mx;
	Segment() {}
	Segment(Point p, Point q) {
		l = Line(p, q);
		if (!l.pX) mn = min(p.x, q.x), mx = max(p.x, q.x);
		else mn = min(p.y, q.y), mx = max(p.y, q.y);
	}
} d[N];
 
double vec[N];
int sz;

double calc(double alpha) {
	sz = 0;
	for (int i = 0; i < n; ++i) {
		double x, inter;
		if (d[i].l.intersect(alpha, x, inter) && (double)d[i].mn - eps <= x && (double)d[i].mx + eps >= x) {
			vec[++sz] = inter;
		}
	}
	sort(vec + 1, vec + sz + 1);
	double res = 0.0;
	for (int i = 2; i <= sz; i += 2) {
		res += vec[i] - vec[i-1];
	}
	return res;
}
 
vector<int> z;
vector<double> vz;
vector<double> valY;
vector<double> vals;

void prepare(double alpha) {
	valY.push_back(alpha);
	vals.push_back(calc(alpha));
}

int main() {
	freopen("QBPIZZA.inp", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) scanf("%d %d", &a[i].x, &a[i].y), z.push_back(a[i].y);
	for (int i = 0; i < n; ++i) {
		d[i] = Segment(a[i], a[(i + 1) % n]);
		if (a[i].y == a[(i + 1) % n].y) {
			cnt[a[i].y + MAX] += abs(a[i].x - a[(i + 1) % n].x);
		}
	}
	sort(z.begin(), z.end());
	z.resize(distance(z.begin(), unique(z.begin(), z.end())));

	for (auto Y : z) {
		double A = 2.0 * calc((double)Y + 1e-9) - calc((double)Y + 2e-9);
		double B = 2.0 * calc((double)Y - 1e-9) - calc((double)Y - 2e-9);
		double C = cnt[Y + MAX];
		vz.push_back((A + B + C) / 2.0);

		prepare((double)Y - 1e-9);
		prepare((double)Y + 1e-9);
	}

	cout << setprecision(7) << fixed;
	while(m--) {
		int Y; cin >> Y;
		if (Y > z.back() || Y < z[0]) { cout << "0.000000\n"; continue; }
		int p = lower_bound(z.begin(), z.end(), Y) - z.begin();
		if (z[p] == Y) { cout << vz[p] << '\n'; continue; }

		p = upper_bound(valY.begin(), valY.end(), (double)Y) - valY.begin();
		assert(p > 0 && p < valY.size());
		
		double ta = Y - valY[p-1];
		double tb = valY[p] - Y;
		double ans = (vals[p] + tb / ta * vals[p-1]) * ta / (ta + tb);

		cout << ans << '\n';
	}
} 