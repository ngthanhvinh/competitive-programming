#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

#define fi first
#define se second

typedef pair<int,int> ii;
typedef pair<ii, int> II;

const int N = 5010;
const long long INF = 1e15;

int n;
ii x[N];
II a[N];
long long f[N][N];
int c[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i].fi;
    for (int i = 1; i <= n; ++i) cin >> x[i].se, a[i] = II(x[i], i);
    sort(a + 1, a + n + 1, greater<II>());

    for (int i = 0; i <= n; ++i) for (int j = 0; j < N; ++j) f[i][j] = -INF;
    f[0][0] = 0;

    for (int i = 1; i <= n; ++i) for (int j = 0; j <= n; ++j) {
        if (j > 0) f[i][j] = max(f[i][j], f[i-1][j-1]);
        if (j < n) f[i][j] = max(f[i][j], f[i-1][j+1] + a[i].fi.se);
    }

    printf("%lld\n", f[n][0]);
    int i = n, j = 0;
    while(i > 0) {
        if (j > 0 && f[i][j] == f[i-1][j-1]) { c[i] = 1; --j; --i; continue; }
        if (j < n && f[i][j] == f[i-1][j+1] + a[i].fi.se) { c[i] = -1; ++j; --i; continue; }
    }

    stack <int> s;
    for (int i = 1; i <= n; ++i) {
        if (c[i] == 1) s.push(i);
        else {
            int u = s.top(); s.pop();
            printf("%d %d\n", a[u].se, a[i].se);
        }
    }
}
