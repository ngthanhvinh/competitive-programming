#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q, k;
int a[N];
long long T[N << 2];
int mx[N << 2];

#define mid ((l + r) >> 1)
void merge(int v) {
	T[v] = T[v << 1] + T[v << 1 | 1];
	mx[v] = max(mx[v << 1], mx[v << 1 | 1]);
}

void build(int v, int l, int r) {
	if (l == r) { T[v] = mx[v] = a[l]; return; }
	build(v << 1, l, mid); build(v << 1 | 1, mid + 1, r);
	merge(v);
}

void upd(int v, int l, int r, int x, int val) {
	if (l > r || l > x || r < x) return;
	if (l == r) { T[v] = mx[v] = val; return; }
	upd(v << 1, l, mid, x, val); upd(v << 1 | 1, mid + 1, r, x, val);
	merge(v);
}

void divide(int v, int l, int r, int L, int R) {
	if (l > r || R < l || L > r) return;
	if (L <= l && r <= R) {
		if (mx[v] == 0) return;
		if (l == r) {
			T[v] /= k; mx[v] /= k;
			return;
		}
	}
	divide(v << 1, l, mid, L, R); divide(v << 1 | 1, mid + 1, r, L, R);
	merge(v);
}

long long get(int v, int l, int r, int L, int R) {
	if (l > r || R < l || L > r) return 0;
	if (L <= l && r <= R) return T[v];
	return get(v << 1, l, mid, L, R) + get(v << 1 | 1, mid + 1, r, L, R);
}
#undef mid

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build(1, 1, n);

	while(q--) {
		int type, l, r; cin >> type >> l >> r;
		if (type == 1) {
			upd(1, 1, n, l, r);
		} else if (type == 2) {
			if (k != 1) divide(1, 1, n, l, r);
		} else {
			printf("%lld\n", get(1, 1, n, l, r));
		}
	}
}