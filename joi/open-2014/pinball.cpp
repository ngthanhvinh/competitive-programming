#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;
const int N = 300005;

struct SegmentTree {
	long long T[N << 2];
	void init() {
		for (int i = 1; i < 4 * N; ++i) T[i] = inf;
	}
	
	#define mid ((l + r) >> 1)
	void upd(int v, int l, int r, int pos, long long val) {
		if (l > r || l > pos || r < pos) return;
		if (l == r) { T[v] = min(T[v], val); return; }
		upd(v << 1, l, mid, pos, val); upd(v << 1 | 1, mid + 1, r, pos, val);
		T[v] = min(T[v << 1], T[v << 1 | 1]);
	}

	long long get(int v, int l, int r, int L, int R) {
		if (l > r || R < l || L > r) return inf;
		if (L <= l && r <= R) return T[v];
		return min(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
	}
	#undef mid
} seg;

int n, m;
int a[N], b[N], c[N], d[N];
long long f[N][2];

vector<int> z;
void solve(int id) {
	seg.init();
	z.clear();
	for (int i = 1; i <= m; ++i) {
		z.push_back(a[i]);
		z.push_back(b[i]);
		z.push_back(c[i]);
	}
	z.push_back(1);
	sort(z.begin(), z.end()); z.resize(distance(z.begin(), unique(z.begin(), z.end())));

	seg.upd(1, 1, z.size(), 1, 0);
	for (int i = 1; i <= m; ++i) {
		int A = lower_bound(z.begin(), z.end(), a[i]) - z.begin() + 1;
		int B = lower_bound(z.begin(), z.end(), b[i]) - z.begin() + 1;
		int C = lower_bound(z.begin(), z.end(), c[i]) - z.begin() + 1;

		f[i][id] = min(inf, seg.get(1, 1, z.size(), A, B) + d[i]);
		seg.upd(1, 1, z.size(), C, f[i][id]);
	}
}

void rot(int &x) { x = n + 1 - x; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> m >> n;
	for (int i = 1; i <= m; ++i) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	}
	solve(0);

	for (int i = 1; i <= m; ++i) {
		rot(a[i]); rot(b[i]); rot(c[i]);
		swap(a[i], b[i]);
	}
	solve(1);

	long long ans = inf;
	for (int i = 1; i <= m; ++i) {
		long long cur = f[i][0] + f[i][1];
		if (cur >= inf) continue;
		ans = min(ans, cur - d[i]);
	}

	if (ans == inf) printf("-1\n"); else printf("%lld\n", ans);
}