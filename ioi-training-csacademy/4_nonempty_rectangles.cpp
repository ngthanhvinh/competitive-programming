#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int inf = 1e9 + 7;

#define x first
#define y second

int n;
pair<int,int> a[N];
int cnt[N];
vector<int> z; int maxX[N];
bool valid;

// Segment Tree
struct SegmentTree {
	int mx[N << 2];
	void reset() {
		for (int i = 1; i <= 4 * (z.size() + 10); ++i) mx[i] = 0;
	}

	#define mid ((l + r) >> 1)
	void upd(int v, int l, int r, int pos, int val) {
		if (l > r || pos < l || pos > r) return;
		if (l == r) {
			mx[v] = max(mx[v], val); return;
		}
		upd(v << 1, l, mid, pos, val); upd(v << 1 | 1, mid + 1, r, pos, val);
		mx[v] = max(mx[v], val);
	}
	int get(int v, int l, int r, int L, int R) { // max
		if (l > r || R < l || L > r) return 0;
		if (L <= l && r <= R) return mx[v];
		return max(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
	}
	#undef mid
} seg;

void go() {
	if (!valid) return;
	sort(a + 1, a + n + 1);
	seg.reset();
	for (int i = 1; i <= z.size(); ++i) maxX[i] = 0;

	int l = 1;
	while(l <= n) {
		int r = l;
		int lst = 0;
		while(r <= n && a[l].x == a[r].x) {
			int coorY = lower_bound(z.begin(), z.end(), a[r].y) - z.begin() + 1;
			int cur = seg.get(1, 1, z.size(), lst + 1, coorY);
			
			if (cur > maxX[coorY]) { valid = false; return; }

			seg.upd(1, 1, z.size(), coorY, a[r].x);
			maxX[coorY] = a[l].x;
			lst = coorY;
			++r;
		}
		l = r;
	}
}

void solve() {
	scanf("%d", &n);
	valid = true;
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &a[i].x, &a[i].y);
	}
	z.clear();
	for (int i = 1; i <= n; ++i) {
		z.push_back(a[i].y);
	}
	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end());

	// solve
	go();
	for (int i = 1; i <= n; ++i) a[i].x = 1e9 + 1 - a[i].x; // rotate
	go();

	printf("%d\n", valid);
}

int main() {
	int tt; scanf("%d", &tt);
	while(tt--) solve();
}