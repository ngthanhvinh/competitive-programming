#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef vector<int> vi;

int n, m;
vector <vi> a, l, r, d, u;

long long get_sum() {
    long long res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            res += a[i][j];
        }
    }
    return res;
}

long long solve() {
    cin >> n >> m;
    a.assign(n+2, vi(m+2, 0));
    l.assign(n+2, vi(m+2, 0));
    r.assign(n+2, vi(m+2, 0));
    u.assign(n+2, vi(m+2, 0));
    d.assign(n+2, vi(m+2, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    long long res = 0;
    while(true) {
        res += get_sum();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                l[i][j] = (a[i][j-1] != 0) ? a[i][j-1] : l[i][j-1];
            }
            for (int j = m; j >= 1; --j) {
                r[i][j] = (a[i][j+1] != 0) ? a[i][j+1] : r[i][j+1];
            }
        }
        for (int j = 1; j <= m; ++j) {
            for (int i = 1; i <= n; ++i) {
                u[i][j] = (a[i-1][j] != 0) ? a[i-1][j] : u[i-1][j];
            }
            for (int i = n; i >= 1; --i) {
                d[i][j] = (a[i+1][j] != 0) ? a[i+1][j] : d[i+1][j];
            }
        }
        
        // for (int i = 1; i <= n; ++i) {
        //     for (int j = 1; j <= m; ++j) {
        //         cerr << a[i][j] << ' ';
        //     }
        //     cerr << endl;
        // }

        bool eliminated = false;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) if (a[i][j]) {
                int sum = l[i][j] + r[i][j] + u[i][j] + d[i][j];
                int num = (l[i][j] != 0) + (r[i][j] != 0) + (u[i][j] != 0) + (d[i][j] != 0);
                if (sum > num * a[i][j]) {
                    a[i][j] = 0;
                    eliminated = true;
                }
            }
        }

        // cerr << eliminated << endl;
        if (!eliminated) break;
    }

    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int nt; cin >> nt;
    for (int it = 1; it <= nt; ++it) {
        cout << "Case #" << it << ": " << solve() << endl;
    }
}