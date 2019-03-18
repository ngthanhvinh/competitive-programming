#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const double ANG = 0.00001;
const double SIN = sin(ANG);
const double COS = cos(ANG);
const double EPS = 1e-6;

int n, m, ans;
int x, y;
bool boundary, cur;

struct Point {
	double x; double y;
} a[N], q;
pair <Point, Point> e[N];

void rot(Point &p) { // rotate
	p.x = x * COS - y * SIN;
	p.y = x * SIN + y * COS;
} 

double cross(Point O, Point A, Point B) {
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &x, &y);
		rot(a[i]);
	}
	a[n].x = a[0].x, a[n].y = a[0].y;

	for (int i = 0; i < n; ++i) {
		e[i] = {a[i], a[i + 1]};
		if (a[i].y > a[i + 1].y) swap(e[i].first, e[i].second);
	}

	while(m--) {
		scanf("%d %d", &x, &y);
		rot(q);

		boundary = false;
		for (int i = 0; i < n; ++i) {
			boundary |= (abs(cross(q, e[i].first, e[i].second)) <= EPS && e[i].first.y <= q.y && q.y <= e[i].second.y);
		}
		if (boundary) {
			++ans; continue;
		}

		cur = 0;
		for (int i = 0; i < n; ++i) {
			cur ^= (e[i].first.y <= q.y && 
							q.y <= e[i].second.y && 
							cross(e[i].first, e[i].second, q) < 0);
		}

		ans += cur;
	}

	printf("%d\n", ans);
}