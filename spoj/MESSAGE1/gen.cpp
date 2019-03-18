#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("message1.inp", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n = 50, m = 50;
    cout << 1 << endl;
    cout << n << ' ' << m << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) { int c = rand() % 26; cout << (char)(c + 'a'); }
        cout << endl;
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) { int c = rand() % 26; cout << (char)(c + 'a'); }
        cout << endl;
    }
}
