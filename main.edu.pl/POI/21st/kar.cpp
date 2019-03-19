#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> card;
#define fi first
#define se second
#define ff(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define le (k << 1)
#define ri ((k<<1)|1)
#define mid ((l + r) >> 1)
const int N = 200010;

int n, m;
bool T[N<<2][2][2];
card a[N];

void build(int k, int l, int r) {
	if (l > r) return;
	if (l == r) { T[k][0][0] = T[k][1][1] = 1; T[k][0][1] = T[k][1][0] = 0; return; }
	build(le, l, mid); build(ri, mid+1, r);
	ff(st, 0, 1) ff(en, 0, 1) T[k][st][en] = 0;
	ff(stLe, 0, 1) ff(enLe, 0, 1) ff(stRi, 0, 1) ff(enRi, 0, 1) {
		int ml, mr;
		if (enLe == 0) ml = a[mid].fi; else ml = a[mid].se;
		if (stRi == 0) mr = a[mid+1].fi; else mr = a[mid+1].se;
		T[k][stLe][enRi] = max(T[k][stLe][enRi], (T[le][stLe][enLe] && T[ri][stRi][enRi] && ml <= mr));
	}
}

void upd(int k, int l, int r, int x, card v) {
	if (x < l || x > r || l > r) return;
	if (l == r) { a[x] = v; T[k][0][0] = T[k][1][1] = 1; T[k][0][1] = T[k][1][0] = 0; return; }
	upd(le, l, mid, x, v); upd(ri, mid+1, r, x, v);
	ff(st, 0, 1) ff(en, 0, 1) T[k][st][en] = 0;
	ff(stLe, 0, 1) ff(enLe, 0, 1) ff(stRi, 0, 1) ff(enRi, 0, 1) {
		int ml, mr;
		if (enLe == 0) ml = a[mid].fi; else ml = a[mid].se;
		if (stRi == 0) mr = a[mid+1].fi; else mr = a[mid+1].se;
		T[k][stLe][enRi] = max(T[k][stLe][enRi], (T[le][stLe][enLe] && T[ri][stRi][enRi] && ml <= mr));
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
	build(1, 1, n);
	cin >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		card c1 = a[u], c2 = a[v];
		upd(1, 1, n, u, c2); 
		upd(1, 1, n, v, c1);
		bool ans = 0; ff(i, 0, 1) ff(j, 0, 1) ans = max(ans, T[1][i][j]);
		if (ans) printf("TAK\n");
		else printf("NIE\n");
	}
	
}