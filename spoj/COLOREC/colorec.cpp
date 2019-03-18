#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int,int> Point;
#define x first
#define y second

const int N = 100010;

int n, c;
Point a[N];
vector<Point> yCoor[410];
int cnt[5][5];
long long ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", &a[i].x, &a[i].y, &c), a[i].x += 200, a[i].y += 200, yCoor[a[i].y].push_back(Point(a[i].x, c));

    for (int i = 0; i <= 400; ++i) if (yCoor[i].size())
        sort(yCoor[i].begin(), yCoor[i].end()),
        yCoor[i].resize(distance(yCoor[i].begin(), unique(yCoor[i].begin(), yCoor[i].end())));

    for (int i = 0; i <= 399; ++i) for (int j = i+1; j <= 400; ++j) if (yCoor[i].size() && yCoor[j].size()) {
        int ptr = 0; memset(cnt, 0, sizeof cnt);
        for (int k = 0; k < yCoor[i].size(); ++k) {
            while(ptr < yCoor[j].size() && yCoor[j][ptr].x < yCoor[i][k].x) ++ptr;
            if (ptr < yCoor[j].size() && yCoor[j][ptr].x == yCoor[i][k].x) {
                int u = yCoor[j][ptr].y, v = yCoor[i][k].y;
                if (u > v) swap(u, v);
                cnt[u][v]++;
            }
        }
        ans += 1ll * cnt[1][2] * cnt[3][4];
        ans += 1ll * cnt[1][3] * cnt[2][4];
        ans += 1ll * cnt[1][4] * cnt[2][3];
    }
    printf("%lld\n", ans);
}
