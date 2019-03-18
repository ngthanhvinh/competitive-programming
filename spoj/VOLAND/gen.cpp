#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("voland.inp", "w", stdout);
    //freopen("voland.out", "w", stdout);
    srand(time(NULL));
    int n, m, a, b, k;
    n = rand() % 30 + 1, m = rand() % 30 + 1, a = rand() % n + 1, b = rand() % m + 1, k = rand() % 2 + 1;
    cout << n << ' ' << m << ' ' << a << ' ' << b << ' ' << k << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cout << rand() % 2000000 - 1000000 << ' ';
        cout << endl;
    }
}
