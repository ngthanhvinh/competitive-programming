#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int r = 10, c = 10;
    int t = 10;
    cout << t << endl;
    for (int it = 1; it <= t; ++it) {
        cout << r << ' ' << c << endl;
        for (int i = 1; i <= r; ++i) {
            for (int j = 1; j <= c; ++j) {
                cout << rand() % 1000000 + 1 << ' ';
            }
            cout << endl;
        }
    }
}