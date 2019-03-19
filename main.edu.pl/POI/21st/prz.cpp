#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;

int n, k, c[N], m, l, x[N], y[N];
int px[N], py[N];
int en[N], st[N], nrx[N], nry[N];
bool checkR[N], checkL[N];
vector <int> ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> c[i];
	cin >> m >> l;
	for (int i = 1; i <= m; i++) cin >> x[i], px[x[i]] = i;
	for (int i = 1; i <= l; i++) cin >> y[i], py[y[i]] = i;
	nrx[0] = 0, nry[0] = n;
	for (int i = 1; i <= n; i++) {
		en[c[i]] = i; nrx[i] = 0;
		if (c[i] == x[1]) nrx[i] = i;
		else if (px[c[i]]) nrx[i] = nrx[en[x[px[c[i]]-1]]];
	}
	for (int i = n; i >= 1; i--) {
		st[c[i]] = i; nry[i] = n;
		if (c[i] == y[1]) nry[i] = i;
		else if (py[c[i]]) nry[i] = nry[st[y[py[c[i]]-1]]];
	}
	int need = x[m];
	for (int i = 1; i <= k; i++) if (en[i]) checkR[i] = 1;
	int l = 1, r = 0;
	
	int cnt = 0;
	for (int i = 1; i <= n; i++) if (c[i] == need) {
		int lo = nrx[i], hi = nry[i];
		while(r <= hi) { if (r == en[c[r]]) { checkR[c[r]] = 0; if (checkL[c[r]]) cnt--; } r++; }
		while(l < lo) { if (l == st[c[l]]) { checkL[c[l]] = 1; if (checkR[c[l]]) cnt++; } l++; }
		if (cnt > 0) ans.push_back(i);
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) cout << ans[i] << ' '; cout << endl;
}