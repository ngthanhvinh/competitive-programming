#include <bits/stdc++.h>
using namespace std;

void gen() {
    int N = 300, M = 300;
    cout << N << ' ' << M << endl;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) cout << 1000000 << ' ';
        cout << endl;
    }
}

int main() {
    freopen("input.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0); srand(time(NULL));
    int T = 100; cout << T << endl;
    while(T--)
        gen();
}
