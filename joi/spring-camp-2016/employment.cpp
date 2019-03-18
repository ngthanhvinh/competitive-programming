#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m, a[N], b[N];
int T[N * 8], lz[N * 8], ans[N * 2];
bool vis[N];
vector<int> z;

struct Query {
	int type; int pos; int x;
} query[N];

// IT
#define mid ((l + r) >> 1)
void build(int v, int l, int r) {
	if (l > r) return;
	if (l == r) { T[v] = ans[l]; return; }
	build(v << 1, l, mid); build(v << 1 | 1, mid + 1, r);
	T[v] = max(T[v << 1], T[v << 1 | 1]);
}

void push(int v, int l, int r) {
	if (lz[v] == 0) return;
	if (l < r) lz[v << 1] += lz[v], lz[v << 1 | 1] += lz[v];
	T[v] += lz[v]; lz[v] = 0;
}

void upd(int v, int l, int r, int L, int R, int val) {
	push(v, l, r);
	if (l > r || R < l || L > r) return;
	if (L <= l && r <= R) { lz[v] += val; push(v, l, r); return; }
	upd(v << 1, l, mid, L, R, val); upd(v << 1 | 1, mid + 1, r, L, R, val);
	T[v] = max(T[v << 1], T[v << 1 | 1]);
}

int get(int v, int l, int r, int pos) {
	push(v, l, r);
	if (l > r || pos < l || r < pos) return 0;
	if (l == r) return T[v];
	return max(get(v << 1, l, mid, pos), get(v << 1 | 1, mid + 1, r, pos));
}
#undef mid
// -----------------------------------------------------------------------

int get(int x) {
	return get(1, 1, z.size(), x);
}

void upd(int pos, int x, int val) {
	int mn = min(a[pos - 1], a[pos + 1]), mx = max(a[pos - 1], a[pos + 1]);
	if (x > mx) upd(1, 1, z.size(), mx + 1, x, +1 * val);
	upd(1, 1, z.size(), 1, min({mn, mx, x}), -1 * val);
}

void init() {
	vector< pair<int,int> > buf;
	for (int i = 1; i <= n; ++i) buf.push_back(make_pair(a[i], i));
	sort(buf.begin(), buf.end());

	int ptr = n - 1;
	int cnt = 0;
	for (int i = z.size(); i >= 1; --i) {
		while(ptr >= 0 && buf[ptr].first >= i) {
			int pos = buf[ptr].second;
			vis[pos] = true;
			if (vis[pos - 1] && vis[pos + 1]) --cnt;
			else if (!vis[pos - 1] && !vis[pos + 1]) ++cnt;
			--ptr;
		}
		ans[i] = cnt;
	}

	build(1, 1, z.size());
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), z.push_back(a[i]);

	for (int i = 1; i <= m; ++i) {
		scanf("%d", &query[i].type);
		if (query[i].type == 1) scanf("%d", &query[i].x);
		else scanf("%d%d", &query[i].pos, &query[i].x);
		z.push_back(query[i].x);
	}

	sort(z.begin(), z.end()); // z.size() <= 400000
	z.erase(unique(z.begin(), z.end()), z.end());

	// init
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(z.begin(), z.end(), a[i]) - z.begin() + 1;
	}
	init(); // correct

	// solve
	for (int i = 1; i <= m; ++i) {
		if (query[i].type == 1) {
			query[i].x = lower_bound(z.begin(), z.end(), query[i].x) - z.begin() + 1;
			printf("%d\n", get(query[i].x));
		} else {
			query[i].x = lower_bound(z.begin(), z.end(), query[i].x) - z.begin() + 1;
			upd(query[i].pos, a[query[i].pos], -1); // old
			a[query[i].pos] = query[i].x;
			upd(query[i].pos, a[query[i].pos], +1); // new
		}
	}
}