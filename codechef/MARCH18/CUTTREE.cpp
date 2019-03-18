#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
const int mod = 1e9 + 7;

int n;
vector<int> g[N];
long long cnt[N];
long long t[N];
int sumt[N]; // modulo 1e9 + 7
int nchild[N], dep[N];
bool was[N];

void dfs(int u, int p) {
    nchild[u] = 1;
    for (int &v : g[u]) if (v != p && !was[v]) {
        dep[v] = dep[u] + 1;
        dfs(v, u);
        nchild[u] += nchild[v];
    }
}

int find_centroid(int u, int p, int r) {
    for (int &v : g[u]) if (v != p && !was[v]) {
        if (nchild[v] * 2 >= nchild[r]) return find_centroid(v, u, r);
    }
    return u;
}

// for FFT
typedef complex <double> base;
const double PI = acos(-1);

int a[N], b[N];
base fa[N], wlen_pw[N];
int rev[N];
int sz, lg; // size, log

void calc_rev() {
    for (int i = 0; i < sz; ++i) {
        rev[i] = 0;
        for (int j = 0; j < lg; ++j) if (i >> j & 1) rev[i] |= (1 << lg - j - 1);
    }
}

void fft(base a[], bool invert) {
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

void multiply(int a[], int na, int val) { // a * a, [0... na - 1]
    sz = 1; lg = 0;
    while(sz < na) sz <<= 1, ++lg;
    sz <<= 1, ++lg;
    calc_rev();

    for (int i = 0; i < sz; ++i) fa[i] = base(0);
    for (int i = 0; i < na; ++i) fa[i] = base(a[i]);

    fft(fa, false);
    for (int i = 0; i < sz; ++i) fa[i] *= fa[i];
    fft(fa, true);

    for (int i = 0; i < sz; ++i) {
        long long cur = (long long) (fa[i].real() + 0.5);
        cnt[i] += val * cur;
    }
}

base pa[N][2], pb[N][2];
const int BASE = sqrt(mod) + 3;

void mod_multiply(int a[], int b[], int na, int nb) {
    sz = 1; lg = 0;
    while(sz < max(na, nb)) sz <<= 1, ++lg;
    sz <<= 1, ++lg;
    calc_rev();

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < sz; ++j) pa[i][j] = pb[i][j] = base(0);
        for (int j = 0; j < na; ++j) pa[i][j] = a[j] % BASE, a[j] /= BASE;
        for (int j = 0; j < nb; ++j) pb[i][j] = b[j] % BASE, b[j] /= BASE;
        fft(pa[i], false);
        fft(pb[i], false);
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            int k = i + j;
            
        }
    }
}

// ------------------------------------------------------
int go(int u, int p) {
    int ret = dep[u];
    a[dep[u]]++;
    b[dep[u]]++;
    for (int &v : g[u]) if (v != p && !was[v]) {
        ret = max(ret, go(v, u));
    }
    return ret;
}

void solve(int u) {
    dfs(u, u);
    u = find_centroid(u, u, u);
    dep[u] = 0;
    was[u] = true;
    dfs(u, u);

    // solve
    int maxdep = 0;
    for (int &v : g[u]) if (!was[v]) {
        int curmax = go(v, u);
        maxdep = max(curmax, maxdep);
        multiply(a, curmax + 1, -1);
        // reset
        for (int i = 0; i <= curmax; ++i) a[i] = 0;
    }

    ++b[0];
    multiply(b, maxdep + 1, +1);
    // reset
    for (int i = 0; i <= maxdep; ++i) b[i] = 0;

    // recursively solve the subtrees of u
    for (int &v : g[u]) if (!was[v]) solve(v);
}

int binpow(int a, int b) {
    int ret = 1;
    while(b) {
        if (b & 1) ret = 1LL * ret * a % mod; a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    solve(1);

    // prepare
    fact[0] = 1; for (int i = 1; i < N; ++i) fact[i] = 1LL * fact[i - 1] * i % mod;
    ifact[0] = 1; for (int i = 1; i < N; ++i) ifact[i] = binpow(fact[i], mod - 2);
    --n;
    for (int i = 0; i <= n; ++i) a[i] = 1LL * cnt[i] * fact[n - i] % mod;
    for (int i = 0; i <= n; ++i) b[i] = ifact[i];

    mod_multiply(a, b, res, n + 1, n + 1);

    for (int i = 0; i <= n; ++i) {
        int cur = res[n - i];
            cur = 1LL * cur * fact[n - i] % mod;
            cur = 1LL * cur * ifact[n] % mod;
        printf("%d\n", cur);
    }
}