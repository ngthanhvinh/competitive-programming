#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int inf = 1e9 + 7;
struct Rock { int x; int y; int m; } a[N], b[N];

int n;
long long MIN[2], MAX[2];
long long mn[2], mx[2];
long long ans = 1e18;
bool did[N];

long long solve(int mask) {
    mn[0] = MIN[0], mn[1] = MIN[1];
    mx[0] = MAX[0], mx[1] = MAX[1];
    if (mask & 1) swap(mn[0], mn[1]);
    if (mask & 2) swap(mx[0], mx[1]);

    if (mx[0] < mn[0] || mx[1] < mn[1]) return 1e18;
    for (int i = 1; i <= n; ++i) b[i] = a[i], did[i] = 0;

    long long mincost = 0;
    // TODO
    for (int i = 1; i <= n; ++i) {
        bool swapped = false;
        if (b[i].x < mn[0] || b[i].x > mx[0]) swap(b[i].x, b[i].y), swapped = true;
        if (b[i].y < mn[1] || b[i].y > mx[1]) swap(b[i].x, b[i].y), swapped = true;
        if (b[i].x < mn[0] || b[i].x > mx[0] || b[i].y < mn[1] || b[i].y > mx[1]) return 1e18;
        if (swapped) mincost += b[i].m, did[i] = 1;
    }

    return mincost;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].m;
    }
    int pos_min0, pos_max0;
    for (int j = 0; j < 2; ++j) MIN[j] = inf, MAX[j] = -inf;

    for (int i = 1; i <= n; ++i) {
        if (MIN[0] > min(a[i].x, a[i].y)) {
            MIN[0] = min(a[i].x, a[i].y);
            pos_min0 = i;
        }
        if (MAX[0] < max(a[i].x, a[i].y)) {
            MAX[0] = max(a[i].x, a[i].y);
            pos_max0 = i;
        }
    }

    // find MAX[1], MIN[1]
    for (int i = 1; i <= n; ++i)
        MIN[1] = min(MIN[1], (long long)max(a[i].x, a[i].y));
    for (int i = 1; i <= n; ++i)
        MAX[1] = max(MAX[1], (long long)min(a[i].x, a[i].y));

    long long fence = 2LL * (MAX[0] + MAX[1] - MIN[0] - MIN[1]);

    int ans_mask;
    for (int mask = 0; mask < 4; ++mask) {
        long long cur = solve(mask);
        if (ans > cur) {
            ans_mask = mask;
            ans = cur;
        }
    }

    printf("%lld %lld\n", fence, ans);
    solve(ans_mask);
    for (int i = 1; i <= n; ++i) printf("%d", did[i]); printf("\n");
}
