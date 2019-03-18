#include <iostream>
#include <cstdio>
#include <utility>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,int> Point;
typedef pair<Point, int> ii;
const int N = 1010;

int n;
Point a[N];
vector <ii> vec;
#define x first
#define y second

void print_answer(int x, int y, int z) {
    printf("%d %d %d\n", x, y, z);
    exit(0);
}

bool cmp(ii a, ii b) {
    return (1ll * a.x.x * b.x.y < 1ll * a.x.y * b.x.x || (1ll * a.x.x * b.x.y == 1ll * a.x.y * b.x.x && a.y < b.y));
}

bool is_equal(Point a, Point b) {
    return 1ll * a.x * b.y == 1ll * a.y * b.x;
}

bool is_equal(int a, int b) {
    return ((a > n && b > n) || (a <= n && b <= n));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= 2 * n; ++i) cin >> a[i].x >> a[i].y;

    for (int i = 1; i <= 2 * n; ++i) {
        vec.clear();
        for (int j = 1; j <= 2 * n; ++j) if (j != i) vec.push_back(ii(Point(a[j].x - a[i].x, a[j].y - a[i].y), j));
        sort(vec.begin(), vec.end(), cmp);
        for (int j = 1; j < (int)vec.size(); ++j) {
            if (is_equal(vec[j-1].x, vec[j].x) && !(is_equal(vec[j-1].y, vec[j].y) && is_equal(vec[j-1].y, i) && is_equal(vec[j].y, i))) {
                print_answer(vec[j-1].y, vec[j].y, i);
            }
        }
    }

    printf("-1\n");
}
