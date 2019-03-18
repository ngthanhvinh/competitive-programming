#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 100;
const int inf = 1e9 + 100;

struct data {
	int l; int r; int len;
	bool operator < (const data &rhs) const {
		return len < rhs.len;
	}
} a[500005];

int n, m;
int T[N << 2], lz[N << 2];
vector<int> z, zlen;
int ans = inf;

#define mid ((l + r) >> 1)
void push(int v, int l, int r) {
	if (!lz[v]) return;
	if (l < r) lz[v << 1] += lz[v], lz[v << 1 | 1] += lz[v];
	T[v] += lz[v]; lz[v] = 0;
}

void upd(int v, int l, int r, int L, int R, int val) {
	push(v, l, r);
	if (l > r || R < l || L > r) return;
	if (L <= l && r <= R) { lz[v] += val; push(v, l, r); return; }
	upd(v << 1, l, mid, L, R, val);
	upd(v << 1 | 1, mid + 1, r, L, R, val);
	T[v] = max(T[v << 1], T[v << 1 | 1]);
}
#undef mid

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].l, &a[i].r), a[i].len = a[i].r - a[i].l;
		z.push_back(a[i].l);
		z.push_back(a[i].r);
		zlen.push_back(a[i].len);
	}

	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end());

	for (int i = 1; i <= n; ++i) {
		a[i].l = lower_bound(z.begin(), z.end(), a[i].l) - z.begin();
		a[i].r = lower_bound(z.begin(), z.end(), a[i].r) - z.begin();
	}

	sort(a + 1, a + n + 1);
	sort(zlen.begin(), zlen.end());

	//for (int i = 1; i <= n; ++i) cerr << a[i].l << ' ' << a[i].r << ' ' << a[i].len << endl;

	// solve
	int pl = 1;
	int pr = 1;
	for (int i = 0; i < zlen.size(); ++i) {
		while(pl < pr && a[pl].len < zlen[i]) {
			upd(1, 0, z.size() - 1, a[pl].l, a[pl].r, -1), ++pl;
		}
		while(pl <= n && a[pl].len < zlen[i]) ++pl;

		if (pr < pl) pr = pl;

		while(T[1] < m && pr <= n) {
			upd(1, 0, z.size() - 1, a[pr].l, a[pr].r, +1), ++pr;
		}

		if (T[1] >= m) {
			ans = min(ans, a[pr - 1].len - zlen[i]);
		}
	}

	printf("%d\n", ans == inf ? -1 : ans);
}