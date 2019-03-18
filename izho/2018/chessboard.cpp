#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, k, nrec;
int lx[N], ly[N], rx[N], ry[N];
long long ans = 1e18;

int get(int t, int l, int r) {
    // count the number of x such that l <= x <= r and (x / k) % 2 == t
    if (l / k == r / k) {
        if ((l / k) % 2 == t) return r - l + 1; else return 0;
    }
    int ret = 0;

    if ((l / k) % 2 == t) ret += ((l / k) + 1) * k - l;
    if ((r / k) % 2 == t) ret += r - (r / k) * k + 1;
    
    l = (l / k) + 1;
    r = (r / k) - 1;

    if (l % 2 != t) ++l;
    if (r % 2 != t) --r;
    
    ret += max(0, (r - l) / 2 + 1) * k;

    return ret;
}

void solve() {
    for (int t = 0; t < 2; ++t) {
        int row[2] = {0, 0}, col[2] = {0, 0};
        for (int i = 0; i < 2; ++i) {
            row[i] = get(i, 0, n - 1);
            col[i] = get(i, 0, n - 1);
        }
        // black cells: (x, y) such that (x + y) == t (modulo 2)
        long long cur = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) if ((i + j) % 2 == t) {
                cur += 1LL * row[i] * col[j];
            }
        }
        for (int rec = 1; rec <= nrec; ++rec) {
            for (int i = 0; i < 2; ++i) {
                row[i] = get(i, lx[rec], rx[rec]);
                col[i] = get(i, ly[rec], ry[rec]);
            }
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    if ((i + j) % 2 == t) cur -= 1LL * row[i] * col[j];
                    else cur += 1LL * row[i] * col[j];
                }
            }
        }
        ans = min(ans, cur);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> nrec;
    for (int i = 1; i <= nrec; ++i) {
        cin >> lx[i] >> ly[i] >> rx[i] >> ry[i];
        --lx[i]; --ly[i]; --rx[i]; --ry[i];
    }
    for (k = 1; k < n; ++k) if (n % k == 0) {
        solve();
    }
    cout << ans << endl;
}