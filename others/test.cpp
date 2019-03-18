#include <bits/stdc++.h>
using namespace std;

int myrand() {
    bool sign = 1;
    int val = rand() % 100;
    if (sign) return val; else return -val;
}

int main() {
    freopen("input.txt", "w", stdout);
    srand(time(NULL));
    int n = 50;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) cout << myrand() << ' '; cout << endl;
    for (int i = 1; i <= n; ++i) cout << myrand() << ' '; cout << endl;
    
    for (int i = 2; i <= n; ++i) {
        cout << rand() % (i - 1) + 1 << ' ' << i << endl;
    }
}