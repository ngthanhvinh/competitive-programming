#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int inf = 1e9;
int n;
int a[N];
int cnt[N];

struct SegmentTree {
	int T[N << 2];
	int lz[N << 2];

	void reset() {
		memset(T, 0, sizeof T);
		memset(lz, 0, sizeof lz);
	}

	#define mid ((l + r) >> 1)

	void build(int v, int l, int r) {
		if (l > r) return;
		if (l == r) { T[v] = l; return; }
		build(v << 1, l, mid); build(v << 1 | 1, mid + 1, r);
		T[v] = min(T[v << 1], T[v << 1 | 1]);
	}

	void push(int v, int l, int r) {
		if (!lz[v]) return;
		if (l < r) lz[v << 1] += lz[v], lz[v << 1 | 1] += lz[v];
		T[v] += lz[v];
		lz[v] = 0;
	}

	void upd(int v, int l, int r, int L, int R) {
		push(v, l, r);
		if (l > r || R < l || L > r) return;
		if (L <= l && r <= R) { ++lz[v]; push(v, l, r); return; }
		upd(v << 1, l, mid, L, R); upd(v << 1 | 1, mid + 1, r, L, R);
		T[v] = min(T[v << 1], T[v << 1 | 1]);
	}

	int get(int v, int l, int r, int L, int R) {
		push(v, l, r);
		if (l > r || R < l || L > r) return inf;
		if (L <= l && r <= R) return T[v];
		return min(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
	}
	#undef mid
} seg;

int main() {
	freopen("greedy.in", "r", stdin);
	freopen("greedy.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i], a[i] = n - a[i];
	
	seg.reset();
	seg.build(1, 1, n);

	seg.upd(1, 1, n, 1, a[1]);
	for (int i = 2; i <= n; ++i) {
		int sum = 0;
		int mn = seg.get(1, 1, n, 2, i);
		if (mn <= i) return cout << n - i + 1 << endl, 0;
		seg.upd(1, 1, n, 1, a[i]);
	}

	cout << 0 << endl;
}