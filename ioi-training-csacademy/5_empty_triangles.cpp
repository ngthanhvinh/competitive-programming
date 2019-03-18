#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

struct Point {
	int x; int y;
	double ang;
	long long norm;

	void init() {
		ang = atan2(y, x); 
		norm = 1LL * x * x + 1LL * y * y;
	}
	bool operator < (const Point &rhs) const {
		return ang < rhs.ang || (ang == rhs.ang && norm < rhs.norm);
	}
} a[N], p, q;	

long long ccw(Point O, Point A, Point B) {
	A.x -= O.x; A.y -= O.y; B.x -= O.x; B.y -= O.y;
	return 1LL * A.x * B.y - 1LL * B.x * A.y;
}

// SEGMENT TREE
vector<Point> visible[N << 2];
Point buf[N];
Point convex[N];

void build(int v, int l, int r) {
	if (l == r) {
		visible[v].push_back(a[l]); return;
	}

	// build the convex hull of a[l...r]
	int sz = 0;
	for (int i = l; i <= r; ++i) buf[sz++] = a[i];
	sort(buf, buf + sz, [&](Point u, Point v) {
		return u.x < v.x || (u.x == v.x && u.y < v.y);
	});
	
	int k = 0;
	for (int i = 0; i < sz; ++i) {
		while(k >= 2 && ccw(convex[k - 2], convex[k - 1], buf[i]) <= 0) --k;
		convex[k++] = buf[i]; 
	}
	for (int i = sz - 2, t = k + 1; i >= 0; --i) {
		while(k >= t && ccw(convex[k - 2], convex[k - 1], buf[i]) <= 0) --k;
		convex[k++] = buf[i];
	}
	--k;

	// create { vector<Point> visible[v] }
	for (int i = k - 1; i > 0; --i) {
		if (ccw({0,0}, convex[i], convex[(i + 1) % k]) <= 0)
			visible[v].push_back(convex[i]);
		else break;
	}
	reverse(visible[v].begin(), visible[v].end());

	visible[v].push_back(convex[0]);
	for (int i = 0; i < k - 1; ++i) {
		if (ccw({0,0}, convex[i], convex[(i + 1) % k]) <= 0) 
			visible[v].push_back(convex[(i + 1) % k]);
		else break;
	}

	// update to the left and right children
	int mid = ((l + r) >> 1);
	build(v << 1, l, mid); build(v << 1 | 1, mid + 1, r);
}

bool search(const vector<Point> &pts) { // with points p and q (p < q)
	int low = 0, high = pts.size() - 1;
	while(low < high) {
		int mid = ((low + high) >> 1);
		if (ccw(p, q, pts[mid]) > ccw(p, q, pts[mid + 1])) high = mid;
		else low = mid + 1;
	}

	return ccw(p, q, pts[low]) >= 0;
}

bool get(int v, int l, int r, int L, int R) {
	if (l > r || R < l || L > r) return 0;
	if (L <= l && r <= R) return search(visible[v]);

	int mid = ((l + r) >> 1);
	bool lef = get(v << 1, l, mid, L, R);
	if (lef) return 1;
	else return get(v << 1 | 1, mid + 1, r, L, R);
}

int n, m;

bool query() {
	if (q < p) swap(p, q); // p < q
	int l = lower_bound(a + 1, a + n + 1, p) - a;
	int r = upper_bound(a + 1, a + n + 1, q) - a - 1;
	return get(1, 1, n, l, r);
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &a[i].x, &a[i].y), a[i].init();
	}
	sort(a + 1, a + n + 1);
	build(1, 1, n);

	while(m--) {
		scanf("%d %d %d %d", &p.x, &p.y, &q.x, &q.y);
		p.init(); q.init();

		bool res = query();
		if (res) puts("Y"); else puts("N");
	}
}