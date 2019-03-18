#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

long long h, sum;
long long already;
int n;
long long p[N];

bool check(long long nday, bool flag = 0) {
    // already + (nday - 3) * sum
    if (nday - 3 >= (h - already + sum - 1) / sum) return true;
    
    long long cur = sum * (nday - 3) + already;
    for (int i = 0; i < n; ++i) {
        cur += p[i];
        assert(cur >= 0);
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
    for (int i = 0; i < n; ++i) cin >> p[i], sum += p[i];

    // whether the snail can exit the well in day 0/1?
    // day 0
    long long cur = 0;
    for (int i = 0; i < n; ++i) {
        cur += p[i];
        cur = max(cur, 0LL);
        if (cur >= h) {
            return cout << 0 << ' ' << i << endl, 0;
        }
    }
    
    if (cur <= 0) return cout << -1 << ' ' << -1 << endl, 0;

    long long last_cur = cur;
    // day 1
    for (int i = 0; i < n; ++i) {
        cur += p[i];
        cur = max(cur, 0LL);
        if (cur >= h) {
            return cout << 1 << ' ' << i << endl, 0;
        }
    }

    if (cur <= last_cur) return cout << -1 << ' ' << -1 << endl, 0;
    
    already = cur;
    
    long long low = 3, high = 1e12;
    while(low < high) {
        long long mid = ((low + high) >> 1);
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    
    check(low, 1);
}