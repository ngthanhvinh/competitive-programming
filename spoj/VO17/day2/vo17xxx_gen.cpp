#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("vo17xxx.inp", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    srand(time(NULL));
    int N = 20;
    cout << N << ' ' << rand() % 1000000 + 1 << endl;
    for (int i = 1; i <= N; ++i) {
        cout << rand() % 1000000 + 1 << endl;
    }
}
