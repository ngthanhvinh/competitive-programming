#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);
typedef complex<double> base;

const int N = 1 << 22;

int q, k;
base wlen_pw[N];
int a[N];
int rev[N];
base fa[N], fb[N];
int ans[N];

// FFT
void fft(base a[], int n, bool invert) {
    for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int len = 2; len <= n; len <<= 1) {
        int len2 = len >> 1;
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen (cos(ang), sin(ang));

        wlen_pw[0] = base(1);
        for (int i = 1; i < len2; ++i) wlen_pw[i] = wlen_pw[i-1] * wlen;

        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len2; ++j) {
                base u = a[i + j], v = a[i + j + len2] * wlen_pw[j];
                a[i + j] = u + v;
                a[i + j + len2] = u - v;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < n; ++i) a[i] /= n;
    }
}

void calc_rev(int n, int logn) {
    for (int i = 0; i < n; ++i) {
        rev[i] = 0;
        for (int j = 0; j < logn; ++j) {
            if (i >> j & 1) rev[i] |= (1 << logn - j - 1);
        }
    }
}

void multiply(int a[], int b[], int &na, int nb) { // a * b -> a
    int low = max(na, nb), logn = 0, n;
    for (n = 1; n < low; n <<= 1) ++logn;
    n <<= 1; ++logn;
    calc_rev(n, logn);

    for (int i = 0; i < n; ++i) fa[i] = fb[i] = 0;
    for (int i = 0; i < na; ++i) fa[i] = base(a[i]);
    for (int i = 0; i < nb; ++i) fb[i] = base(b[i]);

    fft(fa, n, false);
    fft(fb, n, false);

    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    fft(fa, n, true);

    for (int i = 0; i < n; ++i) {
        a[i] = ((long long)(fa[i].real() + 0.5) > 0);
    }

    na = n;
}

void pw(int a[], int k) {
    ans[0] = 1;
    int n = 1024;
    int na = 1024;
    while(k) {
        if (k & 1) multiply(ans, a, n, na);
        multiply(a, a, na, na);
        k >>= 1;
    }
    assert(n <= N);
    assert(na <= N);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> q >> k;
    for (int i = 0; i < q; ++i) {
        int x; cin >> x;
        a[x] = 1;
    }

    pw(a, k);
    for (int i = 1; i < N; ++i) if (ans[i]) {
        printf("%d ", i);
    }
    printf("\n");
}