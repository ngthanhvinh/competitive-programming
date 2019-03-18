#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("rbull.inp", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    srand(time(NULL));
    int n = rand() % 100 + 1, m = rand() % 100 + 1;
    cout << n << ' ' << m << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int r = rand() % 2;
            cout << (r ? '*' : '.');
        }
        cout << endl;
    }
    /*
    int q = 100;
    while(q--) {
        int x, y; x = rand() % n + 1, y = rand() % m + 1;
        int d = min( min(x-1, y-1), min(n-x, m-y) );
        if (d == 0) cout << x << ' ' << y << ' ' << 0 << endl;
        else cout << x << ' ' << y << ' ' << rand() % d + 1 << endl;
    }
    */
}
