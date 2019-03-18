#include <bits/stdc++.h>
using namespace std;

struct Node {
	Node *le, *ri;
	long long T;
	long long lz, lzle, lzri;
	Node() { le = NULL; ri = NULL; T = 0; lz = 0; lzle = 0; lzri = 0; }
	~Node() { delete le; delete ri; }

	#define mid ((l + r) >> 1)
	
	void push(long long l, long long r) {
		if (l < r) lzle += lz, lzri += lz;
		if (le != NULL) le -> lz += lzle, lzle = 0; 
		if (ri != NULL) ri -> lz += lzri, lzri = 0;
		T += lz;
		lz = 0;
	}
	void upd(long long l, long long r, long long L, long long R, long long val) {
		push(l, r);
		if (l > r || R < l || L > r) return;
		if (L <= l && r <= R) {
			lz = val; push(l, r); return;
		}
		if (le == NULL) le = new Node(), le -> lz += lzle, lzle = 0; 
		if (ri == NULL) ri = new Node(), ri -> lz += lzri, lzri = 0;
		le -> upd(l, mid, L, R, val);
		ri -> upd(mid + 1, r, L, R, val);
		T = max(le -> T, ri -> T);
	}
	long long get(long long l, long long r, long long L, long long R) {
		push(l, r);
		if (l > r || R < l || L > r) return -1e18;
		if (L <= l && r <= R) return T;
		if (R <= mid) return (le == NULL ? lzle : le -> get(l, mid, L, R));
		if (L > mid) return (ri == NULL ? lzri : ri -> get(mid + 1, r, L, R));

		long long ans = max((le == NULL ? lzle : le -> get(l, mid, L, R)), (ri == NULL ? lzri : ri -> get(mid + 1, r, L, R)));
		return ans;
	}
} *seg = new Node();

int n, q; 
long long inf;
map <long long, int> cnt;
vector <long long> vec;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> inf;
	seg -> upd(1, inf, 1, inf, -2);
	for (int i = 1; i <= n; ++i) {
		long long v; cin >> v;
		if (cnt[v] == 0) seg -> upd(1, inf, v, v, v);
		++cnt[v];
		vec.push_back(v);
		seg -> upd(1, inf, v + 1, inf, -v);
	}

	printf("%d\n", (seg -> get(1, inf, 1, inf) < 0));

	sort(vec.begin(), vec.end());
	
	cin >> q;
	while(q--) {
		int event; cin >> event; 
		int c; cin >> c;
		while(c--) {
			long long v; cin >> v;
			cnt[v] += event;
			if ((event == 1 && cnt[v] == 1) || (event == -1 && cnt[v] == 0)) seg -> upd(1, inf, v, v, v * event);
			seg -> upd(1, inf, v + 1, inf, -v * event);
		}
		printf("%d\n", (seg -> get(1, inf, 1, inf) < 0));
	}
}