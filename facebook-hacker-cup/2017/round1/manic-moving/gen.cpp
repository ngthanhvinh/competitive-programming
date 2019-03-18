#include <bits/stdc++.h>
using namespace std;

void gen() {
    int N = 10, K = 2, M = 9;
    cout << N << ' ' << M << ' ' << K << endl;
    for (int i = 2; i <= N; ++i) {
        int u = i, v = rand() % (i - 1) + 1;
        cout << u << ' ' << v << ' ' << rand() % 1000 + 1 << endl;
    }
    for (int i = 1; i <= K; ++i) {
        int u = 0, v = 0; while(u == v) u = rand() % N + 1, v = rand() % N + 1;
        cout << u << ' ' << v << endl;
    }
}

int main() {
    freopen("input.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0); srand(time(NULL));
    int T = 10;
    cout << T << endl;
    while(T--)
        gen();
}
