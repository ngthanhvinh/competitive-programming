#include <bits/stdc++.h>
using namespace std;

const int N = 510;

int inv[N];
int A, n, mod;

int pw(int a, int b) {
    int ret = 1;
    while(b) {
        if (b & 1) ret = 1LL * ret * a % mod; a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ret;
}

void add(int &x, int y) {
    x += y; while(x >= mod) x -= mod;
}

vector <int> mul(vector <int> dp1, vector <int> dp2, int t) {
    // a.size() == b.size() == n + 1
    vector<int> tmp(n + 1, 0);
    for (int i = 0; i <= n; ++i) {
        int powt = 1;
        int mul = 1;
        int cur;
        for (int j = i; j >= 0; --j) {
            if (j != i) {
                mul = 1LL * mul * (t - j) % mod;
                mul = 1LL * mul * inv[i - j] % mod;
                // C(t - j, i - j)
            }
            cur = 1LL * dp2[j] * powt % mod;
            cur = 1LL * cur * mul % mod;

            add(tmp[i], cur);
            powt = 1LL * powt * t % mod;
        }
    }

    vector<int> ret(n + 1, 0);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            add(ret[i], 1LL * dp1[j] * tmp[i - j] % mod);
        }
    }

    return ret;
}

vector<int> pw(vector<int> a, int k) {
    if (k == 1) return a;
    vector<int> aa = pw(a, k / 2);
    aa = mul(aa, aa, k / 2);
    if (k & 1) {
        for (int i = n; i >= 1; --i) {
            aa[i] = (1LL * aa[i - 1] * k + aa[i]) % mod;
        }
    }
    return aa;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> A >> n >> mod;

    inv[0] = 1; 
    for (int i = 1; i < N; ++i) inv[i] = pw(i, mod - 2);

    vector<int> vec(n + 1, 0); // A = 1
    vec[0] = 1; vec[1] = 1;
    vector<int> poly = pw(vec, A);

    int res = poly[n];

    for (int i = 1; i <= n; ++i) {
        res = 1LL * res * i % mod;
    }
    
    cout << res << endl;
}