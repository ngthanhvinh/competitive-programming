#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int Q = 300005;
const int md = 1e9 + 7;

int n, L, q, qq, a[N], old_a[N];
int st[N], en[N], e[N], TIME;
vector<int> G[N];
vector<int> buf[N], old_buf[N];
int up[N], dn[N], old_up[N], old_dn[N];
int query[Q];
int lst, O;
vector<int> ans;

void euler(int u) {
	st[u] = ++TIME;
	e[TIME] = u;
	for (int v : G[u]) euler(v);
	en[u] = TIME;
}

void add(int &x, int y) {
	x += y; while(x >= md) x -= md; while(x < 0) x += md;
}
// -----------------------------------------------------------------------------------------
struct FenwickTree {
	vector<int> T;
	int sz;
	FenwickTree(int sz=0): sz(sz) { T.assign(sz + 10, 0); }
	void upd(int x, int v) { for (; x <= sz; x += x & -x) add(T[x], v); }
	int get(int x) { int ret = 0; for (; x > 0; x -= x & -x) add(ret, T[x]); return ret; }
} oldBIT[N], BIT[N];

int get(int val, int l, int r) { // get_dn
	int pl = lower_bound(buf[val].begin(), buf[val].end(), l) - buf[val].begin() + 1;
	int pr = upper_bound(buf[val].begin(), buf[val].end(), r) - buf[val].begin();
	if (pl > pr) return 0;
	int ret = BIT[val].get(pr) - BIT[val].get(pl - 1);
	if (ret < 0) ret += md;
	return ret;
}
void upd(int val, int x, int v) { // up_dn
	x = lower_bound(buf[val].begin(), buf[val].end(), x) - buf[val].begin() + 1;
	BIT[val].upd(x, v);
}


int get_up(int val, int x) { // point query
	x = lower_bound(buf[val].begin(), buf[val].end(), x) - buf[val].begin() + 1;
	return BIT[val].get(x);
}
void upd_up(int val, int l, int r, int v) { // range update
	int pl = lower_bound(buf[val].begin(), buf[val].end(), l) - buf[val].begin() + 1;
	int pr = upper_bound(buf[val].begin(), buf[val].end(), r) - buf[val].begin();
	if (pl > pr) return;
	BIT[val].upd(pl, v);
	BIT[val].upd(pr + 1, -v);
}
int old_get_up(int val, int x) { // point query
	x = lower_bound(old_buf[val].begin(), old_buf[val].end(), x) - old_buf[val].begin() + 1;
	return oldBIT[val].get(x);
}
void old_upd_up(int val, int l, int r, int v) { // range update
	int pl = lower_bound(old_buf[val].begin(), old_buf[val].end(), l) - old_buf[val].begin() + 1;
	int pr = upper_bound(old_buf[val].begin(), old_buf[val].end(), r) - old_buf[val].begin();
	if (pl > pr) return;
	oldBIT[val].upd(pl, v);
	oldBIT[val].upd(pr + 1, -v);
}

vector<int> get_dn[N];
int old_get_dn(int val, int l, int r) { // get_dn
	int pl = lower_bound(old_buf[val].begin(), old_buf[val].end(), l) - old_buf[val].begin() + 1;
	int pr = upper_bound(old_buf[val].begin(), old_buf[val].end(), r) - old_buf[val].begin();
	if (pl > pr) return 0;
	int ret = get_dn[val][pr] - get_dn[val][pl - 1];
	if (ret < 0) ret += md;
	return ret;
} 
// --------------------------------------------------------------------------------------------

void calc_dn(int u) {
	for (int v : G[u]) calc_dn(v);
	dn[u] = get(a[u] + 1, st[u] + 1, en[u]);
	if (a[u] == L) dn[u] = 1;
	upd(a[u], st[u], dn[u]);
}

void calc_up(int u) {
	old_up[u] = old_get_up(old_a[u], st[u]);
	if (old_a[u] == 1) old_up[u] = 1;

	up[u] = get_up(a[u], st[u]); // get sum
	if (a[u] == 1) up[u] = 1;

	upd_up(a[u] + 1, st[u] + 1, en[u], up[u]);
	old_upd_up(a[u] + 1, st[u] + 1, en[u], up[u]);
	for (int v : G[u]) calc_up(v);
}

void prepare() { // prepare for a new batch of queries
	// up
	for (int val = 1; val <= L; ++val) {
		BIT[val] = FenwickTree(buf[val].size());
		oldBIT[val] = FenwickTree(old_buf[val].size());
	}
	calc_up(0);
	// dn
	for (int val = 1; val <= L; ++val) {
		BIT[val] = FenwickTree(buf[val].size());
	}
	calc_dn(0);

	//for (int i = 0; i < n; ++i) printf("%d -> %d old_up = %d up = %d dn = %d\n", i, a[i], old_up[i], up[i], dn[i]);
}

void solve() {
	// lst is the answer of the last query
	for (int i = 0; i < n; ++i) {
		lst -= 1LL * old_up[i] * old_dn[i] % md; 
		if (lst < 0) lst += md;

		lst += 1LL * up[i] * (a[i] == L ? 1 : old_get_dn(a[i] + 1, st[i] + 1, en[i])) % md;
		if (lst >= md) lst -= md;

		ans.push_back(lst);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> L >> q;
	for (int i = 1; i < n; ++i) {
		int p; cin >> p; G[p].push_back(i);
	}
	for (int i = 0; i < n; ++i) cin >> a[i];

	for (int i = 0; i < q; ++i) cin >> query[i];
	qq = q; // qq: original q
	while(q % n) {
		if (q >= n) query[q] = query[q - n];
		else query[q] = a[q];
		++q;
	}

	// process queries
	euler(0);
	for (int i = 1; i <= TIME; ++i) buf[a[e[i]]].push_back(i);
	prepare();
	for (int i = 0; i < n; ++i) if (a[i] == 1) add(lst, dn[i]);

	for (int ntime = 0; ntime < q / n; ++ntime) {
		// reset
		ans.clear();
		for (int i = 0; i < n; ++i) {
			old_up[i] = up[i], old_dn[i] = dn[i];
			up[i] = dn[i] = 0;
			old_a[i] = a[i];
			a[i] = query[ntime * n + i];
		}
		for (int i = 1; i <= L; ++i) old_buf[i].swap(buf[i]), buf[i].clear();
		for (int i = 1; i <= TIME; ++i) buf[a[e[i]]].push_back(i);
		// old_get_dn
		for (int i = 1; i <= L; ++i) {
			get_dn[i].clear();
			get_dn[i].push_back(0);
			for (int j = 1; j <= old_buf[i].size(); ++j) 
				get_dn[i].push_back((get_dn[i][j-1] + old_dn[e[old_buf[i][j-1]]]) % md);
		}

		// solve
		prepare();
		solve();

		for (int i = ntime * n; i < qq && i < (ntime + 1) * n; ++i) {
			add(O, 1LL * (i + 1) * ans[i - ntime * n] % md);
		}
	}

	cout << O << endl;
}