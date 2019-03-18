#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef pair<int, ii> query;

vector <query> input;

int main() {
    freopen("vo17bach.inp", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 200;
    /*
    cout << t << endl;
    while(t--) {
        long long N = (rand() % 1000000000 + 1) * (rand() % 1000000000 + 1), K = (rand() % 1000000000 + 1) * (rand() % 1000000000 + 1);
        if (N < K) swap(N, K);
        cout << 1 << ' ' << N << ' ' << K << endl;
    }
    */
    cout << t << endl;
    for (int i = 1; i <= t; ++i) {
        int N = rand() % 100000 + 1, K = rand() % N + 1;
        cout << rand() % 2 << ' ' << N << ' ' << K << endl;
    }
}
