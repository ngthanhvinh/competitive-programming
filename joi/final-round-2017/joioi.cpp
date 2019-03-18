#include <bits/stdc++.h>
using namespace std;
 
const int N = 2005;
const int inf = 1e9 + 7;
 
int n, m;
int a[N][N], tmp[N][N];
int mnR[N][N], mxR[N][N];
int pos[N];
 
void _rotate() {
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) tmp[j][n + 1 - i] = a[i][j];
	swap(n, m);
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) a[i][j] = tmp[i][j];
}
 
int ans = inf;
int mn = inf;
 
bool check(int val) {
	for (int i = 1; i <= n; ++i) {
		pos[i] = m + 1;
		for (int j = 1; j <= m; ++j) if (a[i][j] > mn + val) { pos[i] = j; break; }
	}
	
	for (int i = 1; i <= n; ++i) {
		mnR[i][m + 1] = inf; mxR[i][m + 1] = 0;
		for (int j = m; j >= 1; --j) {
			mnR[i][j] = min(mnR[i][j + 1], a[i][j]);
			mxR[i][j] = max(mxR[i][j + 1], a[i][j]);
		}
	}
 
	int cur = m;
	int cur_min = inf, cur_max = 0;
	for (int i = 1; i <= n; ++i) {
		cur = min(cur, pos[i] - 1);
		cur_min = min(cur_min, mnR[i][cur + 1]);
		cur_max = max(cur_max, mxR[i][cur + 1]);
	}
 
	return cur_max - cur_min <= val;
}
 
void solve() {
	int l = 0, r = inf;
	while(l < r) {
		int mid = ((l + r) >> 1);
		if (check(mid)) r = mid; else l = mid + 1;
	}
	if (check(l)) ans = min(ans, l);
}
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> a[i][j], mn = min(mn, a[i][j]);
	}
	
	solve();
 
	_rotate();
	solve();
 
	_rotate();
	solve();
 
	_rotate();
	solve();
 
	printf("%d\n", ans);	
}