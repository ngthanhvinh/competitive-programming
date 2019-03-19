#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
using namespace std;

const int N = 3010;
typedef pair<int,int> Point;
typedef pair<double, Point> data;
#define x first
#define y second

const double pi = acos(-1.0);
int n; Point a[N];
vector<data> pts;
long long ans;

double angle(Point p) {
    double alpha = atan2(p.y, p.x);
    if (alpha < 0) alpha += 2 * pi;
    return alpha;
}

bool in(double alpha, double beta) {
    return alpha <= beta && beta <= alpha + pi;
}

void solve(Point pivot) {
    pts.clear();
    for (int i = 1; i <= n; ++i) if (a[i] != pivot) {
        Point nxt = Point(a[i].x-pivot.x, a[i].y-pivot.y);
        pts.push_back( data (angle(nxt), nxt) );
        pts.push_back( data (angle(nxt) + 2 * pi, nxt) );
    }
    sort(pts.begin(), pts.end());

    int sz = pts.size(), pl = 0, pr = 0;
    long long xSum = 0, ySum = 0;
    for (int i = 0; i < pts.size(); ++i) if (pts[i].first <= pi) xSum += pts[i].second.x, ySum += pts[i].second.y, pr = i+1;
    for (int i = 0; i < pts.size(); ++i) {
        if (pts[i].first >= 2 * pi) break;
        while(pl < pts.size() && !in(pts[i].first, pts[pl].first)) xSum -= pts[pl].second.x, ySum -= pts[pl].second.y, pl++;
        while(pr < pts.size() && in(pts[i].first, pts[pr].first)) xSum += pts[pr].second.x, ySum += pts[pr].second.y, pr++;
        ans -= 1ll * xSum * pts[i].second.y - 1ll * ySum * pts[i].second.x;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
    for (int i = 1; i <= n; ++i) solve(a[i]);
    ans /= 3;
    printf("%lld.%d", ans / 2, (ans & 1) ? 5 : 0);
}
