#include <bits/stdc++.h>
using namespace std;
const int N = 200010, M = 500010;
#define ll long long 

int n, m, k, d;
struct Node {
	ll t; ll le; ll ri; ll s;
	Node(ll t=0, ll le=0, ll ri=0, ll s=0): t (t), le (le), ri (ri), s (s) {}
	void operator += (int val) { t += val, le += val, ri += val, s += val; }
} tr[N<<2];
void merge(Node &V, const Node &L, const Node &R) {
	V.s = L.s + R.s;
	V.t = max(L.ri + R.le, max(L.t, R.t));
	V.le = max(L.le, L.s + R.le);
	V.ri = max(R.ri, R.s + L.ri);
}
#define mid ((l + r) >> 1)
void build(int v, int l, int r) {
	if (l > r) return;
	if (l == r) { ll val; if (l != n+1) val = -k; else val = 1ll * d * k; tr[v] = Node(val, val, val, val); return; }
	build(2 * v, l, mid); build(2 * v + 1, mid+1, r);
	merge(tr[v], tr[2 * v], tr[2 * v + 1]);
}
void upd(int v, int l, int r, int x, int val) {
	if (l > r || x < l || x > r) return;
	if (l == r) { tr[v] += val; return; }
	upd(2 * v, l, mid, x, val); upd(2 * v + 1, mid+1, r, x, val);
	merge(tr[v], tr[2 * v], tr[2 * v + 1]);
}

int main() {
	scanf("%d%d%d%d", &n, &m, &k, &d);
	build(1, 1, n + 1);
	while(m--) {
		int r, x; scanf("%d%d", &r, &x);
		upd(1, 1, n + 1, r, x);
		//cout << tr[1].t << endl;
		if (tr[1].t > 1ll * k * d) puts("NIE");
		else puts("TAK");
	}
}