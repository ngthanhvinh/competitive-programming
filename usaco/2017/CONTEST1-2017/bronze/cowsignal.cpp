#include <iostream>
#include <cstdio>
using namespace std;

int n, m, k;
char a[11][11];
char b[110][110];

int main() {
    freopen("cowsignal.in", "r", stdin);
    freopen("cowsignal.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> a[i][j];
    for (int i = 0; i < n; ++i) {
        for (int trow = 0; trow < k; ++trow) {
            for (int j = 0; j < m; ++j) {
                for (int tcol = 0; tcol < k; ++tcol) cout << a[i][j];
            }
            cout << endl;
        }
    }
}
