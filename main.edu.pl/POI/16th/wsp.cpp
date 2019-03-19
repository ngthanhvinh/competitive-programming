#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> Point;
#define x first 
#define y second

const int N = 100110;
const long double eps = 1e-9;
int n, m;
Point a[N];
pair <int,int> e[1000010];
int s[N];

Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
long long cross(Point a, Point b) { return 1LL * a.x * b.y - 1LL * a.y * b.x; }
long long ccw(Point a, Point b, Point c) { b = b - a; c = c - a; return cross(b,c); }

bool under(int i, int j, pair <long double, long double> k) {
	long double res = (long double)(k.y - a[i].y) * (a[j].x - a[i].x) - (long double)(k.x - a[i].x) * (a[j].y - a[i].y);
	if (res >= -eps) return 0; else return 1;
}

const int inf = 1e9;
pair <long double, long double> intersection(int a1, int a2, int b1, int b2) {
	if (a2 > b2) return make_pair(inf,inf); // a1 < b1 for sure

	Point A = a[a2] - a[a1], B = a[b2] - a[b1], S = a[b1] - a[a1];

	long long ss = cross(S,B), aa = cross(A,B);
	long double X = a[a1].x + A.x * ((long double)ss / aa);
	long double Y = a[a1].y + A.y * ((long double)ss / aa);
	
	return make_pair(X,Y);
}

pair <long double, long double> hor(int fi, int se) { return intersection(fi, s[fi], se, s[se]); }

bool check(double x1, double x2) { return x1 <= x2 + eps; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		if (u > v) swap(u,v); 
		e[i] = make_pair(u,v);
	}
	sort(e + 1, e + m + 1);

	int cur = m;
	for (int i = n; i >= 1; --i) {
		s[i] = -1;
		int ss = n;
		while(cur >= 1 && e[cur].first == i && e[cur].second == ss) --cur, --ss;
		if (ss > i) s[i] = ss; 
		while(cur >= 1 && e[cur].first == i) --cur;
	}

	// construct convex hull with lines (i, s[i])
	vector <int> L;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == -1) continue;

		if (L.size() >= 1 && ccw(a[L.back()], a[s[L.back()]], a[s[i]]) >= 0) continue;

		while(L.size() >= 2) {
			pair <long double, long double> r = hor(L[L.size()-2], L.back());
			if (!under(i, s[i], r)) L.pop_back(); else break;
		}
		if (L.size() >= 1 && hor(L.back(), i).x == inf) continue;
		if (L.size() >= 1 && s[L.back()] == s[i]) continue;
		L.push_back(i);
	}

	long double ans = 0;
	pair <long double,long double> lst = a[1];
	for (int i = 0; i < (int)L.size() - 1; ++i) {
		pair <long double, long double> cur = hor(L[i], L[i+1]);
		long double len = hypot(cur.x - lst.x, cur.y - lst.y);
		ans += len;
		lst = cur;
	}
	ans += hypot(a[n].x - lst.x, a[n].y - lst.y);

	cout << setprecision(5) << fixed << ans << endl;
}