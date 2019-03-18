#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "w", stdout);
    int n = 20;
    cout << n << ' ' << 10 << endl;
    for (int i = 0; i < (1 << n); ++i) cout << rand() % 9 + 1; cout << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < n; ++j) {
            int cur = rand() % 3;
            if (cur == 2) cout << '?'; else cout << cur;
        }
        cout << endl;
    }
}