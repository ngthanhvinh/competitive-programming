#include <bits/stdc++.h>
using namespace std;
const int N = 100010, MOD = (int)1e9;

int L[N * 80], R[N * 80], T[N * 80], peak, ver[N], ans;
int n, a[N];
#define le (v<<1)
#define ri ((v<<1)|1)
#define mid ((l+r)>>1)

int upd(int v, int l, int r, int x, int val) {
	if(l > r || r < x || l > x) return v;
	if(l == r) { T[++peak] = val; L[peak] = R[peak] = peak; return peak; }
	int u = ++peak;
	L[u] = upd(L[v], l, mid, x, val); R[u] = upd(R[v], mid+1, r, x, val);
	T[u] = max(T[L[u]], T[R[u]]);
	return u;
}

int get(int v, int l, int r, int i, int j) {
	if (l > r || i > r || j < l) return 0;
	if (i <= l && r <= j) return T[v];
	return max(get(L[v], l, mid, i, j), get(R[v], mid+1, r, i, j));
}

void build(int v, int l, int r) {
	if (l > r) return;
	if (l == r) { T[v] = a[l], L[v] = R[v] = v; peak = max(peak, v); return; }
	build(le, l, mid); build(ri, mid+1, r);
	T[v] = max(T[le], T[ri]); L[v] = le, R[v] = ri;
	peak = max(peak, v);
	//printf("%d %d %d %d %d %d\n", v, l, r, L[v], R[v], T[v]);
}

struct Query {
	int type; int a; int b; int c; int d;
	Query(int type=0, int a=0, int b=0, int c=0, int d=0): type (type), a (a), b (b), c (c), d (d) {}
} qu[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	build(1, 1, n);
	
	int R, Q, P=0; 
	scanf("%d%d", &R, &Q);
	for (int i = 1; i <= Q; i++) scanf("%d%d%d%d%d", &qu[i].type, &qu[i].a, &qu[i].b, &qu[i].c, &qu[i].d);
	
	ans = 0; ver[0] = 1;

	while(R--) {
		for (int i = 1; i <= Q; i++) {
			if(qu[i].type == 1) {
				int u = (1ll * ans * qu[i].a + qu[i].c) % n + 1, k = (1ll * ans * qu[i].b + qu[i].d) % MOD + 1;
				++P; ver[P] = upd(ver[P-1], 1, n, u, k);
			}
			else if (qu[i].type == 2) {
				int u = (1ll * ans * qu[i].a + qu[i].c) % n + 1, v = (1ll * ans * qu[i].b + qu[i].d) % n + 1;
				ans = get(ver[P], 1, n, min(u, v), max(u, v));
				printf("%d\n", ans);
			}
			else {
				int x = (1ll * ans * qu[i].a + qu[i].c) % (P + 1);
				ver[++P] = ver[x];
			}
		}
	}
}