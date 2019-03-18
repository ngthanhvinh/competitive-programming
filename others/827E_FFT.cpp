#include <bits/stdc++.h>
using namespace std;

typedef complex <double> base;
const int N = 1 << 22;
const int MAXLEN = 500005;
const double PI = acos(-1);

base fa[N], fb[N], wlen_pw[N];
int n; string s;
int a[N], b[N], c[N], rev[N];
bool check[MAXLEN];
int sz, lg; // for FFT

void fft(base a[], bool invert) { // size: sz
    for (int i = 0; i < sz; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int len = 2; len <= sz; len <<= 1) {
        int len2 = len >> 1;
        double ang = 2 * PI / len * (invert ? -1 : +1);
        base wlen (cos(ang), sin(ang));

        wlen_pw[0] = base(1);
        for (int i = 1; i < len2; ++i) wlen_pw[i] = wlen_pw[i - 1] * wlen;

        for (int i = 0; i < sz; i += len) {
            for (int j = 0; j < len2; ++j) {
                base u = a[i + j], v = a[i + j + len2] * wlen_pw[j];
                a[i + j] = u + v;
                a[i + j + len2] = u - v;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < sz; ++i) a[i] /= sz;
    }
}

void calc_rev() {
    for (int i = 0; i < sz; ++i) {
        rev[i] = 0;
        for (int j = 0; j < lg; ++j) if (i >> j & 1) rev[i] |= (1 << lg - j - 1);
    }
}

void multiply(int a[], int b[], int c[]) {
    sz = 1; lg = 0;
    while(sz < n) sz <<= 1, ++lg;
    sz <<= 1; ++lg;
    calc_rev();

    for (int i = 0; i < sz; ++i) fa[i] = fb[i] = base(0);
    for (int i = 0; i < n; ++i) fa[i] = base(a[i]);
    for (int i = 0; i < n; ++i) fb[i] = base(b[i]);
    fft(fa, false); fft(fb, false);

    for (int i = 0; i < sz; ++i) fa[i] *= fb[i];
    fft(fa, true);

    for (int i = 0; i < sz; ++i) {
        c[i] = ((long long)(fa[i].real() + 0.5) > 0);
    }
}

void solve() {
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'V') a[i] = 1;
        if (s[i] == 'K') b[n - 1 - i] = 1;
    }
    multiply(a, b, c);

    for (int i = 0; i < 2 * n; ++i) {
        if (c[i]) check[abs(i - n + 1)] = true;
    }

    for (int i = 1; i <= n; ++i) if (!check[i]) {
        for (int j = i + i; j <= n; j += i) if (check[j]) check[i] = true;
    }

    // output
    int cnt = 0;
    for (int i = 1; i <= n; ++i) if (!check[i]) ++cnt;
    printf("%d\n", cnt);
    for (int i = 1; i <= n; ++i) if (!check[i]) printf("%d ", i); printf("\n");

    // reset
    for (int i = 0; i < n; ++i) a[i] = b[i] = 0;
    for (int i = 1; i <= n; ++i) check[i] = false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int tt; cin >> tt;
    while(tt--) {
        solve();
    }
}