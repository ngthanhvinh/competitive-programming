#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    srand(time(NULL));
    freopen("scchem.inp", "w", stdout);
    int t, n, m; t = rand() % 10 + 1;
    cout << t << endl;
    while(t--) {
        n = rand() % 10 + 1, m = rand() % 10 + 1;
        cout << n << ' ' << m << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) cout << rand() % 2;
            cout << endl;
        }
    }
}
