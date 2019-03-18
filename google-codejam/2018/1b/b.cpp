#include <bits/stdc++.h>
using namespace std;

const int N = 100020;
const int INF = 1e9;

int n;
int a[N], d[N], b[N], res[N];
vector <int> z;
vector <int> vec[N];

struct SegmentTree {
	struct Node {
		int val;
		int len;
		Node(int val = -INF, int len = -INF) : val(val), len(len) {}
	} t[N << 2];

	#define mid ((l + r) >> 1)

	void reset() {
		for (int i = 1; i <= 4 * (n + 10); ++i) t[i] = Node();
	}

	Node merge(Node lef, Node rig) {
		Node ret = Node();
		if (lef.len == -INF || rig.len == -INF) return ret;
		if (lef.val == -INF || rig.val == -INF || lef.val == rig.val) {
			ret.val = max(lef.val, rig.val);
			ret.len = lef.len + rig.len;
		}
		return ret;
	}

	void upd(int v, int l, int r, int pos, int val) {
		if (r < pos || l > pos) return;
		if (l == r) {
			t[v] = {val, 1}; return;
		}
		upd(v << 1, l, mid, pos, val);
		upd(v << 1 | 1, mid + 1, r, pos, val);
		t[v] = merge(t[v << 1], t[v << 1 | 1]);
	}

	Node get(int v, int l, int r, int L, int R) {
		if (R < l || L > r) return {-INF, 0};
		if (L <= l && r <= R) return t[v];
		return merge(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
	}

	#undef mid
} seg;

void go() {
	for (int i = 1; i <= n; ++i) {
		z.push_back(a[i] + d[i]);
	}
	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end());

	seg.reset();
	for (int i = 1; i <= n; ++i) {
		seg.upd(1, 1, n, i, d[i] - b[i]);
	}
	for (int i = 1; i <= n; ++i) {
		vec[lower_bound(z.begin(), z.end(), d[i] + a[i]) - z.begin() + 1].push_back(i);
	}

	for (int i = 1; i <= z.size(); ++i) {
		for (int &j : vec[i - 1]) seg.upd(1, 1, n, j, d[j] - b[j]);
		for (int &j : vec[i]) seg.upd(1, 1, n, j, -INF);
		for (int &j : vec[i]) {
			int low = j, high = n;
			while(low < high) {
				int mid = ((low + high + 1) >> 1);
				if (seg.get(1, 1, n, j, mid).len == mid - j + 1) low = mid;
				else high = mid - 1;
			}
			res[j] = max(res[j], low - j + 1);
		}
	}

	// reset
	for (int i = 1; i <= z.size(); ++i) vec[i].clear();
	z.clear();
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> d[i] >> a[i] >> b[i];
		res[i] = 0;
	}

	// d[i] + a[i]
	go();
	// d[i] - b[i]
	for (int i = 1; i <= n; ++i) {
		a[i] = -a[i];
		b[i] = -b[i];
		swap(a[i], b[i]);
	}
	go();

	int mx = *max_element(res + 1, res + n + 1);
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (res[i] == mx) ++cnt;
	}

	printf("%d %d\n", mx, cnt);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}