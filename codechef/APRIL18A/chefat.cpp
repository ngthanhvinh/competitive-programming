#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
double a[N];
double t[N << 2], sum[N << 2], lz[N << 2];

double binpow(double a, int b) {
	double ret = 1.0;
	while(b) {
		if (b & 1) ret *= a; a *= a;
		b >>= 1;
	}
	return ret;
}

#define mid ((l + r) >> 1)
void build(int v, int l, int r) {
	lz[v] = 1;
	if (l == r) {
		t[v] = 1.0 - a[l]; sum[v] = a[l]; return;
	}
	build(v << 1, l, mid);
	build(v << 1 | 1, mid + 1, r);
	t[v] = t[v << 1] * t[v << 1 | 1];
	sum[v] = sum[v << 1] + sum[v << 1 | 1];
}

void push(int v, int l, int r) {
	if (lz[v] == 1) return;
	if (l < r) lz[v << 1] *= lz[v], lz[v << 1 | 1] *= lz[v];
	printf("lz = %.10lf\n", lz[v]);
	t[v] = 1 - sum[v] * lz[v] * binpow(1 - lz[v], r - l);
	sum[v] *= lz[v];
	printf("%d %d => %.10lf\n", l, r, t[v]);
	lz[v] = 1;
}

void upd(int v, int l, int r, int L, int R, double val) {
	push(v, l, r);
	if (R < l || L > r) return;
	if (L <= l && r <= R) {
		lz[v] = val; push(v, l, r); return;
	}
	upd(v << 1, l, mid, L, R, val);
	upd(v << 1 | 1, mid + 1, r, L, R, val);
	t[v] = t[v << 1] * t[v << 1 | 1];
	sum[v] = sum[v << 1] + sum[v << 1 | 1];
}

double get(int v, int l, int r, int L, int R) {
	push(v, l, r);
	if (R < l || L > r) return 1;
	if (L <= l && r <= R) return t[v];
	return get(v << 1, l, mid, L, R) * get(v << 1 | 1, mid + 1, r, L, R);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build(1, 1, n);

	while(q--) {
		int type, l, r; cin >> type >> l >> r;
		if (type == 0) {
			// stress
			double res = 1.0;
			for (int i = l; i <= r; ++i) res *= (1.0 - a[i]);
			printf("\t%.10lf\n", res);

			printf("%.10lf\n", get(1, 1, n, l, r));
		} else {
			double val; cin >> val;
			// stress
			for (int i = l; i <= r; ++i) a[i] *= val;

			upd(1, 1, n, l, r, val);
		}
	}
}