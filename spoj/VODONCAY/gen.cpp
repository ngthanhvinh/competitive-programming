#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("vodoncay.inp", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    srand(time(NULL));
    int n = 4000000;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        cout << rand() % 7 + 1 << ' ';
    }
    cout << endl;
}
