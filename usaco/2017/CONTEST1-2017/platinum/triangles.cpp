#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 310;
typedef pair<int,int> Point;
#define x first
#define y second

const double pi = acos(-1.0);
int n;
Point a[N];
Point p[N];
Point pivot;
long long f[N];

double angle(Point u) {
    double alpha = atan2(u.y, u.x);
    return (alpha < 0 ? alpha + 2 * pi : alpha);
}

struct BIT {
    int n; vector<int> T;
    BIT(int n=0): n(n) { T.assign(n + 1, 0); }
    void upd(int x, int v) { for (; x <= n; x += x & -x) T[x] += v; }
    int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += T[x]; return res; }
};

bool cmp(Point u, Point v) { return 1ll * u.x * v.y < 1ll * v.x * u.y; }

vector <int> s;
void solve2(Point A) {
    vector <Point> z;
    for (int i = 0; i < s.size(); ++i) z.push_back(Point(p[s[i]].x-A.x, p[s[i]].y-A.y));
    sort(z.begin(), z.end(), cmp); BIT tr = BIT(z.size());

    for (int i = 0; i < s.size(); ++i) {
        int pos = s[i];
        int poscur = lower_bound(z.begin(), z.end(), Point(p[pos].x-A.x, p[pos].y-A.y), cmp) - z.begin() + 1;
        ++f[tr.get(poscur)];
        tr.upd(poscur, 1);
    }
}

void solve() {
    for (int i = 1; i <= n; ++i) p[i] = Point(a[i].x-pivot.x, a[i].y-pivot.y);
    vector < pair<double, int> > pts;
    for (int i = 1; i <= n; ++i) if (p[i] != Point(0,0) && p[i].y >= 0) {
        double alpha = angle(p[i]);
        if (alpha < pi) pts.push_back( make_pair(alpha, i) );
    }
    sort(pts.begin(), pts.end());
    for (int i = 0; i < (int)pts.size()-1; ++i) {
        s.clear();
        int cur = pts[i].y; double alpha = pts[i].x;
        for (int j = i+1; j < pts.size(); ++j) s.push_back(pts[j].y);
        solve2(p[cur]);
    }
}

int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].x, &a[i].y);
    for (int i = 1; i <= n; ++i) pivot = a[i], solve();
    for (int i = 0; i <= n-3; ++i) printf("%lld\n", f[i]);
}
/*
5
0 0
2 0
0 2
3 3
4 1
*/
