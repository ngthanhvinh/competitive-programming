#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
const int OFFSET = 50000;
const double PI = acos(-1);

typedef complex<double> base;
int q;
base a[N], b[N], c[N];
long long mul[N];
base wlen_pw[N];

int rev(int num, int lg_n) {
    int ret = 0;
    for (int i = 0; i < lg_n; ++i) {
        if (num >> i & 1) ret |= (1 << lg_n - i - 1);
    }
    return ret;
}

void fft(base a[], bool invert) {
    for (int i = 0; i < N; ++i) {
        int rev_i = rev(i, 18);
        if (i < rev_i) swap(a[i], a[rev_i]);
    }

    for (int len = 2; len <= N; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen (cos(ang), sin(ang));

        int len2 = len >> 1;
        wlen_pw[0] = base(1);
        for (int i = 1; i < len2; ++i) {
            wlen_pw[i] = wlen_pw[i - 1] * wlen;
        }
        
        for (int i = 0; i < N; i += len) {
            for (int j = 0; j < len2; ++j) {
                base u = a[i + j], v = a[i + j + len2] * wlen_pw[j];
                a[i + j] = u + v;
                a[i + j + len2] = u - v;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < N; ++i) a[i] /= N;
    }
}

void multiply(base a[], base b[], base c[]) {
    fft(a, false);
    fft(b, false);
    for (int i = 0; i < N; ++i) c[i] = a[i] * b[i];
    fft(c, true);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> q;
    for (int i = 0; i < q; ++i) { int x; cin >> x; a[x + OFFSET] += 1.0; }
    for (int i = 0; i < q; ++i) { int x; cin >> x; b[x + OFFSET] += 1.0; }

    multiply(a, b, c);
    for (int i = 0; i < N; ++i) {
        mul[i] = (long long) (c[i].real() + 0.5);
    }

    long long res = 0;
    for (int i = 0; i < q; ++i) {
        int x; cin >> x; x += 2 * OFFSET;
        res += mul[x];
    }

    cout << res << endl;
}