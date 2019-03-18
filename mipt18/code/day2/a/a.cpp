#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MN = (1 << 19) + 5;
#define REP(i, n) for (int i = 0; i < (n); ++i)

int my_round(double x) {
    if (x < 0) return -my_round(-x);
    return (int) (x + 1e-3);
}

const double PI = acos((double) -1.0);

typedef complex<double> cplex;
int rev[MN];
cplex wlen_pw[MN], fa[MN], fb[MN];

void fft(cplex a[], int n, bool invert) {
    for (int i = 0; i < n; ++i) if (i < rev[i]) swap (a[i], a[rev[i]]);

    for (int len = 2; len <= n; len <<= 1) {
        double alpha = 2 * PI / len * (invert ? -1 : +1);
        int len2 = len >> 1;

        wlen_pw[0] = cplex(1, 0);
        cplex wlen(cos(alpha), sin(alpha));
        for (int i = 1; i < len2; ++i) wlen_pw[i] = wlen_pw[i-1] * wlen;

        for (int i = 0; i < n; i += len) {
            cplex t, *pu = a+i, *pv = a + i + len2,
                    *pu_end = a + i + len2, *pw = wlen_pw;
            for (; pu != pu_end; ++pu, ++pv, ++pw) {
                t = *pv * *pw;
                *pv = *pu - t;
                *pu += t;
            }
        }
    }

    if (invert) REP(i, n) a[i] /= n;
}

void calcRev(int n, int logn) {
    REP(i, n) {
        rev[i] = 0;
        REP(j, logn) if (i & (1 << j)) rev[i] |= 1 << (logn - 1 - j);
    }
}

void mulpoly(int a[], int b[], ll c[], int na, int nb, int &n) {
    int l = max(na, nb), logn = 0;
    for (n = 1; n < l; n <<= 1) ++logn;
    n <<= 1; ++logn;
    calcRev(n, logn);

    REP(i,n) fa[i] = fb[i] = cplex(0);
    REP(i,na) fa[i] = cplex(a[i]);
    REP(i,nb) fb[i] = cplex(b[i]);

    fft(fa, n, false);
    fft(fb, n, false);

    REP(i,n) fa[i] *= fb[i];
    fft(fa, n, true);

    REP(i,n) c[i] = (ll)(fa[i].real() + 0.5);
}
// END OF FFT

const int N = 250005;

string s, t;
int n, m;
ll s4[N], s2[N], t4[N], t2[N];
int a[MN], b[MN];
ll c[MN], d[MN], e[MN], f[MN];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> t >> s;
	n = s.size();
	m = t.size();
	t = ' ' + t;
	s = ' ' + s;

	for (int i = 1; i <= m; ++i) {
		t2[i] = t2[i - 1] + (t[i] - 'a') * (t[i] - 'a');
		t4[i] = t4[i - 1] + (t[i] - 'a') * (t[i] - 'a') * (t[i] - 'a') * (t[i] - 'a');
	}

	for (int i = 1; i <= n; ++i) {
		s2[i] = s2[i - 1] + (s[i] - 'a') * (s[i] - 'a');
		s4[i] = s4[i - 1] + (s[i] - 'a') * (s[i] - 'a') * (s[i] - 'a') * (s[i] - 'a');
	}

	// FFT
	int sz;
	// x^3y
	for (int i = 1; i <= m; ++i) a[i] = (t[i] - 'a') * (t[i] - 'a') * (t[i] - 'a');
	for (int i = 1; i <= n; ++i) b[n - i + 1] = s[i] - 'a';
	mulpoly(a, b, c, m + 1, n + 1, sz);
	// x^2y^2
	for (int i = 1; i <= m; ++i) a[i] = (t[i] - 'a') * (t[i] - 'a');
	for (int i = 1; i <= n; ++i) b[n - i + 1] = (s[i] - 'a') * (s[i] - 'a');
	mulpoly(a, b, d, m + 1, n + 1, sz);
	// xy^3
	for (int i = 1; i <= m; ++i) a[i] = (t[i] - 'a');
	for (int i = 1; i <= n; ++i) b[n - i + 1] = (s[i] - 'a') * (s[i] - 'a') * (s[i] - 'a');
	mulpoly(a, b, e, m + 1, n + 1, sz);
	// xy
	for (int i = 1; i <= m; ++i) a[i] = t[i] - 'a';
	for (int i = 1; i <= n; ++i) b[n - i + 1] = s[i] - 'a';
	mulpoly(a, b, f, m + 1, n + 1, sz);

	// x, y are almost the same <-> (x - y)^2 * (x - y - 1)^2 = 0
	// <-> x^4 - 4x^3y + 6x^2y^2 - 4xy^3 + y^4 - x^2 + 2xy - y^2 = 0
	vector <int> vres;
	for (int i = 1; i <= n - m + 1; ++i) {
		ll cur =  t4[m] + (s4[i + m - 1] - s4[i - 1]) // x^4 + y^4
					  - t2[m] - (s2[i + m - 1] - s2[i - 1]) // - x^2 - y^2
					  - 4ll * c[n - i + 2] // - 4x^3y
					  + 6ll * d[n - i + 2] // + 6x^2y^2
					  - 4ll * e[n - i + 2] // - 4xy^3
					  + 2ll * f[n - i + 2]; // + 2xy
		if (cur == 0) {
			vres.push_back(i);
		}
	}

	printf("%d\n", vres.size());
	for (int &i : vres) {
		printf("%d ", i);
	}
}