#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

long long h, sum;
int n;
long long p[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> h >> n;
    for (int i = 0; i < n; ++i) cin >> p[i];

    // whether the snail can exit the well in day 0?
    for (int i = 0; i < n; ++i) {
        sum += p[i];
        sum = max(sum, 0LL);
        if (sum >= h) {
            return cout << 0 << ' ' << i << endl, 0;
        }
    }
    
    if (sum <= 0) return cout << -1 << ' ' << -1 << endl, 0;

    int nday = 1;
    while(true) {
        for (int i = 0; i < n; ++i) {
            sum += p[i];
            sum = max(sum, 0LL);
            if (sum >= h) return cout << nday << ' ' << i << endl, 0;
        }
        ++nday;
    }
}