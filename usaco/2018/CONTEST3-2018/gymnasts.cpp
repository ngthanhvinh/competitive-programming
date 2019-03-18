#include <bits/stdc++.h>
using namespace std;

// int a[25];
// int c[25];
// int ans;

// void brute(int pos, int mn) {
//     if (pos == n) {
//         bool ok = false;
//         for (int i = 0; i < n; ++i) {
//             if (a[i] == mn) ok = true;
//         }
//         if (!ok) return;

//         ok = true;
//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < a[i]; ++j) c[(i + j) % n]++;
//         }

//         for (int i = 0; i < n; ++i) {
//             if (c[i] != a[i]) { ok = false; break; }
//         }
//         for (int i = 0; i < n; ++i) c[i] = 0;
//         if (ok) {
//             ++ans;
//             //for (int i = 0; i < n; ++i) cout << a[i] << ' '; cout << endl;
//         }
//         return;
//     }
//     for (int i = mn; i <= min(n, mn + 1); ++i) {
//         a[pos] = i;
//         brute(pos + 1, mn);
//     }
// }

const int mod = 1e9 + 7;

int pw(int a, long long b) {
    int ret = 1;
    while(b) {
        if (b & 1) ret = 1LL * ret * a % mod; a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ret;
}

void add(int &x, int y) {
    x += y; while(x >= mod) x -= mod; while(x < 0) x += mod;
}

const int N = 1e6 + 5;

long long n;
int res;
vector<long long> dvs;
long long t[N];
int np[N];
int pr[N];
int nprime;

void sieve() {
    np[0] = np[1] = 1;
    for (int i = 2; i < N; ++i) if (!np[i]) {
        for (int j = i + i; j < N; j += i) np[j] = 1;
        pr[++nprime] = i;
    }
}

int main() {
    freopen("gymnasts.in", "r", stdin);
    freopen("gymnasts.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    cin >> n;
    if (n == 1) {
        printf("1\n"); return 0;
    }
    sieve();
    
    long long tmp = n;
    dvs.push_back(1);

    for (int i = 1; i <= nprime && 1LL * pr[i] * pr[i] <= n; ++i) {
        if (tmp % pr[i] == 0) {
            int cnt = 0;
            while(tmp % pr[i] == 0) ++cnt, tmp /= pr[i];
            
            // add more divisors
            int sz = dvs.size();
            long long p = 1;
            while(cnt--) {
                p *= pr[i];
                for (int j = 0; j < sz; ++j) dvs.push_back(dvs[j] * p);
            }
        }
    }
    if (tmp > 1) {
        int sz = dvs.size();
        for (int j = 0; j < sz; ++j) dvs.push_back(dvs[j] * tmp);
    }

    for (int i = dvs.size() - 1; i >= 0; --i) {
        long long d = dvs[i];
        t[i] = (n - 1) / d;
        for (int j = i + 1; j < dvs.size(); ++j) {
            if (dvs[j] % d == 0) t[i] -= t[j];
        }
        add(res, 1LL * pw(2, d) * t[i] % mod);
    }
 
    add(res, (-n + 2) % mod);
    printf("%d\n", res);
}