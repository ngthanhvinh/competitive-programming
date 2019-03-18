#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const long long inf = 1e18;

struct SegmentTree {
	struct Node {
		long long val; long long pre; long long suf; long long sum;
		Node() { val = -inf; sum = pre = suf = 0; }
	} it[N << 2];

	#define mid ((l + r) >> 1)
	Node merge(Node le, Node ri) {
		Node cur = Node();
		cur.sum = le.sum + ri.sum;
		cur.val = max({le.val, ri.val, le.suf + ri.pre});
		cur.pre = max(le.pre, le.sum + ri.pre);
		cur.suf = max(ri.suf, ri.sum + le.suf);
		return cur;
	}
	void upd(int v, int l, int r, int pos, int val) {
		if (l > r || l > pos || r < pos) return;
		if (l == r) { it[v].val = it[v].pre = it[v].suf = it[v].sum = val; return; }
		upd(v << 1, l, mid, pos, val); upd(v << 1 | 1, mid + 1, r, pos, val);
		it[v] = merge(it[v << 1], it[v << 1 | 1]);
	}
	long long get() { return it[1].val; }
	#undef mid
} seg;

struct Point {
	int x; int y; int w;
	Point(int x=0, int y=0, int w=0): x(x), y(y), w(w) {}
	bool operator < (const Point &rhs) const {
		return y < rhs.y || (y == rhs.y && x < rhs.x);
	}
	Point operator - (Point q) { Point p = *this; return Point(p.x - q.x, p.y - q.y); }
} a[N];

long long cross(Point a, Point b) {
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

long long cmp(pair<int,int> p, pair<int,int> q) {
	long long flag = cross(a[p.second] - a[p.first], a[q.second] - a[q.first]);
	return flag;
}

int n;
vector< pair<int,int> > vec;
long long ans;
int pos[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y >> a[i].w;
	sort(a + 1, a + n + 1);	
	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			vec.push_back(make_pair(i,j));
		}
	}
	sort(vec.begin(), vec.end(), [&](pair<int,int> p, pair<int,int> q) { // (first_point, second_point)
		long long flag = cmp(p, q);
		if (flag != 0) return flag > 0; else return make_pair(a[p.first], a[p.second]) < make_pair(a[q.first], a[q.second]);
	});

	for (int i = 1; i <= n; ++i) pos[i] = i;
	for (int i = 1; i <= n; ++i) seg.upd(1, 1, n, i, a[i].w);
	ans = max(ans, seg.get());

	for (int i = 0; i < vec.size(); ++i) {
		vector< pair<int,int> > Q;
		Q.push_back(vec[i]);
		while(i + 1 < vec.size() && cmp(vec[i], vec[i+1]) == 0) {
			Q.push_back(vec[i+1]); ++i;
		}
		for (auto p : Q) {
			swap(pos[p.first], pos[p.second]);
			seg.upd(1, 1, n, pos[p.first], a[p.first].w);
			seg.upd(1, 1, n, pos[p.second], a[p.second].w);
		}
		ans = max(ans, seg.get());
	}
	cout << ans << endl;
}