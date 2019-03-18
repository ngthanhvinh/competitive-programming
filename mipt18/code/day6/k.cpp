#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 1e9 + 7;
int inv[] = {0, 1, 500000004, 333333336};
#define x first
#define y second

int n, m, k;
pair<int,int> a[N];
int sum0, sum1, sum2, sum3;

void add(int &x, int y) {
	x += y; while(x >= mod) x -= mod; while(x < 0) x += mod;
}

int C(long long n, int k) { // k <= 3
	if (n < k) return 0;
	int ret = 1;
	for (long long i = n - k + 1; i <= n; ++i) {
		ret = 1LL * ret * (i % mod) % mod;
	}
	for (int i = 1; i <= k; ++i) {
		ret = 1LL * ret * inv[i] % mod;
	}
	return ret;
}

void calc() {
	sort(a + 1, a + k + 1);
	int curX = 0;
	int curY;
	int m2 = C(m, 2), m3 = C(m, 3);
	for (int i = 1; i <= k; ) {
		add(sum1, 1LL * (a[i].x - 1 - curX) * m2 % mod);
		add(sum3, 1LL * (a[i].x - 1 - curX) * m3 % mod);
		curX = a[i].x;
		curY = 0;
		while(i <= k && a[i].x == curX) {
			add(sum1, C(a[i].y - 1 - curY, 2));
			add(sum3, C(a[i].y - 1 - curY, 3));
			curY = a[i].y;
			++i;
		}
		add(sum1, C(m - curY, 2));
		add(sum3, C(m - curY, 3));
	}
	add(sum1, 1LL * (n - curX) * m2 % mod);
	add(sum3, 1LL * (n - curX) * m3 % mod);
}

// -----------------------------------------------------
vector <int> z; // for compression

struct SegmentTree {
	#define mid ((l + r) >> 1)
	long long t[N << 2];
	int lz[N << 2];
	void reset() {
		memset(t, 0, sizeof t);
		memset(lz, 0, sizeof lz);
	}
	// (z[r] - z[l - 1]) * t[v]
	void push(int v, int l, int r) {
		if (!lz[v]) return;
		if (l < r) lz[v << 1] += lz[v], lz[v << 1 | 1] += lz[v];
		t[v] += 1LL * (z[r] - z[l - 1]) * lz[v];
		lz[v] = 0;
		return;
	}
	void upd_seg(int v, int l, int r, int L, int R, int val) {
		push(v, l, r);
		if (R < l || L > r) return;
		if (L <= l && r <= R) {
			lz[v] = val; push(v, l, r); return;
		}
		upd_seg(v << 1, l, mid, L, R, val);
		upd_seg(v << 1 | 1, mid + 1, r, L, R, val);
		t[v] = t[v << 1] + t[v << 1 | 1];
	}
	void upd_pos(int v, int l, int r, int pos) {
		push(v, l, r);
		if (r < pos || l > pos) return;
		if (l == r) { t[v] = 0; return; }
		upd_pos(v << 1, l, mid, pos);
		upd_pos(v << 1 | 1, mid + 1, r, pos);
		t[v] = t[v << 1] + t[v << 1 | 1];
	}
	long long get(int v, int l, int r, int L, int R) {
		push(v, l, r);
		if (R < l || L > r) return 0;
		if (L <= l && r <= R) return t[v];
		return get(v << 1, l, mid, L, R) + get(v << 1 | 1, mid + 1, r, L, R);
	}
} seg;

void calc_sum2() {
	sort(a + 1, a + k + 1);
	z.clear();
	seg.reset();

	for (int i = 1; i <= k; ++i) {
		z.push_back(a[i].y);
		z.push_back(a[i].y + 1);
	}
	z.push_back(1);
	z.push_back(m + 1);
	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end());
	int sz = z.size();

	// sweep line
	int curX = 0;
	int curY = 0;
	int s, sum;
	for (int i = 1; i <= k; ) {
		s = a[i].x - 1 - curX;
		add(sum2, 1LL * (1LL * s * (m - 1) % mod) * (seg.t[1] % mod) % mod);
		add(sum2, 1LL * m * (1LL * (m - 1) * C(s, 2) % mod) % mod);
		seg.upd_seg(1, 1, sz - 1, 1, sz - 1, s + 1);

		// this x
		curX = a[i].x;
		curY = 0;
		while(i <= k && a[i].x == curX) {
			int zy = lower_bound(z.begin(), z.end(), a[i].y) - z.begin() + 1;
			sum = (seg.get(1, 1, sz - 1, curY + 1, zy - 1) - (z[zy - 1] - z[curY])) % mod;
			add(sum2, 1LL * sum * max(0, z[zy - 1] - z[curY] - 1) % mod);
			seg.upd_pos(1, 1, sz - 1, zy);
			curY = zy;
			++i;
		}
		sum = (seg.get(1, 1, sz - 1, curY + 1, sz - 1) - (z[sz - 1] - z[curY])) % mod;
		add(sum2, 1LL * sum * max(0, z[sz - 1] - z[curY] - 1) % mod);
	}
	// copy
	s = n - curX;
	add(sum2, 1LL * (1LL * s * (m - 1) % mod) * (seg.t[1] % mod) % mod);
	add(sum2, 1LL * m * (1LL * (m - 1) * C(s, 2) % mod) % mod);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 1; i <= k; ++i) {
		cin >> a[i].x >> a[i].y;
		++a[i].x; ++a[i].y;
	}

	calc();
	// rotate
	swap(n, m);
	for (int i = 1; i <= k; ++i) {
		swap(a[i].x, a[i].y);
	}
	calc();
	sum1 = 1LL * sum1 * max(0LL, (1LL * n * m - k - 2) % mod) % mod;
	calc_sum2();
	for (int i = 1; i <= k; ++i) {
		a[i].x = n + 1 - a[i].x; // flip
	}
	calc_sum2();
	sum0 = C((1LL * n * m - k), 3);

	// overlap
	add(sum1, -2LL * sum2 % mod);
	add(sum1, -3LL * sum3 % mod);

	add(sum0, -sum1);
	add(sum0, -sum2);
	add(sum0, -sum3);

	printf("%d\n", sum0);
}