#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ff(i, a, b) for (int i = a; i <= b; i++)
const int N = 2010;

int n, m;
int a[N][N], tmp[N][N];
int k, r[N][N], c[N][N];
int ans = (int)1e9;

int get(int l, int r, int H[]) { return H[r] - H[l-1]; }

bool f(int x, int y) {
    if (x == 0 || y == 0) return 0;
    int xl = 1, yl = 1, xr = n, yr = m;
    while(xl <= xr && yl <= yr) {
        if (get(yl, yr, r[xl]) <= k) xl++;
        else if (get(yl, yr, r[xr]) <= k) xr--;
        else {
            //cout << get(xl, xr, c[yl]) << endl;
            if (yl < x && get(xl, xr, c[yl]) <= k) yl++;
            else if (yr > y && get(xl, xr, c[yr]) <= k) yr--;
            else return 0;
        }
    }
    return 1;
}

void solve() {
    ff(i, 1, n) ff(j, 1, m) r[i][j] = r[i][j - 1] + a[i][j], c[j][i] = c[j][i - 1] + a[i][j];
    int j = 0;

    ff(i, 1, m) {
        while(j <= i && !f(j, i)) j++;
        //cout << j << ' ' << i << endl;
        if (j <= i) ans = min(ans, n + m - i + j - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> k >> m >> n;
    ff(i, 1, n) ff(j, 1, m) cin >> tmp[i][j], a[i][j] = tmp[i][j];
    solve();
    ff(i, 1, n) ff(j, 1, m) a[j][i] = tmp[i][j];
    swap(n, m);
    solve();
    cout << ans << endl;
}