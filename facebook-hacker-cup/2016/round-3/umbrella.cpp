#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct Raindrop {
	int X; int K; int id;
	bool operator < (const Raindrop &rhs) const { return X < rhs.X || (X == rhs.X && K < rhs.K); }
	bool operator > (const Raindrop &rhs) const { return X < rhs.X || (X == rhs.X && K > rhs.K); }
} a[N];

struct FenwickTree {
	int T[N];
	FenwickTree() { memset(T, 0, sizeof T); }
	void upd(int x, int v) { for (; x < N; x += x & -x) T[x] = max(T[x], v); }
	int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res = max(res, T[x]); return res; }
} BIT;

int n, S;
int f[N], g[N], cnt[N];
int ans;
double line[N];
int id[N];
vector<double> z;

void solve1() {
	z.clear();
	BIT = FenwickTree();
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) {
		line[i] = a[i].K - (double)a[i].X / S;
		z.push_back(line[i]);
	}
	sort(z.begin(), z.end());
	for (int i = 1; i <= n; ++i) id[i] = lower_bound(z.begin(), z.end(), line[i]) - z.begin() + 1;
	for (int i = 1; i <= n; ++i) {
		f[a[i].id] = BIT.get(id[i]) + 1; cnt[id[i]]++; BIT.upd(id[i], cnt[id[i]]);
		if (a[i].X == a[i - 1].X) f[a[i].id] = max(f[a[i].id], f[a[i - 1].id] + 1);
	}
}

void solve2() {
	z.clear();
	BIT = FenwickTree();
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) {
		line[i] = a[i].K + (double)a[i].X / S;
		z.push_back(line[i]);
	}
	sort(z.begin(), z.end());
	for (int i = 1; i <= n; ++i) id[i] = lower_bound(z.begin(), z.end(), line[i]) - z.begin(), id[i] = n - id[i];
	for (int i = 1; i <= n; ++i) {
		g[a[i].id] = BIT.get(id[i]) + 1; cnt[id[i]]++; BIT.upd(id[i], cnt[id[i]]);
		if (a[i].X == a[i - 1].X) g[a[i].id] = max(g[a[i].id], g[a[i - 1].id] + 1);
	}
}

void solve() {
	memset(f, 0, sizeof f); memset(g, 0, sizeof g);
	sort(a + 1, a + n + 1);
	solve1();

	sort(a + 1, a + n + 1, greater<Raindrop>());
	solve2();

	for (int i = 1; i <= n; ++i) ans = max(ans, f[i] + g[i] - 1);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cin >> n >> S;
		for (int i = 1; i <= n; ++i) cin >> a[i].X >> a[i].K, a[i].id = i;
		ans = 0;
		solve();
		for (int i = 1; i <= n; ++i) a[i].X = -a[i].X;
		solve();

		printf("Case #%d: %d\n", it, ans);
	}
}