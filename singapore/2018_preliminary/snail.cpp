#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

long long h, sum;
int n;
long long p[N];

bool check(long long nday, bool flag = 0) {
    if (nday - 1 >= (h + sum - 1) / sum) return true;
    
    long long cur = sum * (nday - 1);
    for (int i = 0; i < n; ++i) {
        cur += p[i];
        cur = max(cur, 0LL);
        if (cur >= h) {
            if (flag) cout << nday - 1 << ' ' << i << endl;
            return true;
        }
    }

    return false;
}

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

    if (1LL * h * n <= 10000) {
        int nday = 1;
        while(true) {
            for (int i = 0; i < n; ++i) {
                sum += p[i];
                sum = max(sum, 0LL);
                if (sum >= h) return cout << nday << ' ' << i << endl, 0;
            }
            ++nday;
        }
        return 0;
    }
    
    long long low = 2, high = 1e12;
    while(low < high) {
        long long mid = ((low + high) >> 1);
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    
    check(low, 1);
}