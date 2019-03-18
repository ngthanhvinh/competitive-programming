#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const int inf = 1e9 + 7;

int n;
int a[N];
int f[2][N << 1][3][4];
int cnt[3];

void mnm(int &x, int y) { if (x > y) x = y; }

int check() {
	int add = 0, res = 0;
	for (int i = 1; i <= n; ++i) res += a[i] == 0;
	for (int i = 1; i <= n; ++i) if (a[i] == 2) {
		bool lef = true;
		for (int j = 1; j < i; ++j) if (a[j]) { lef = false; break; }
		add |= lef;
		break;
	}
	for (int i = n; i >= 1; --i) if (a[i] == 2) {
		bool rig = true;
		for (int j = n; j > i; --j) if (a[j]) { rig = false; break; }
		add |= rig;
		break;
	}

	res += (add ^ 1);
	return res;
}

void solve() {
	cin >> n; 
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cin >> a[i], cnt[a[i]]++;
	if (cnt[0] && cnt[1] && !cnt[2]) {
		printf("-1\n"); return;
	}
	if (!cnt[0] || !cnt[1]) { printf("0\n"); return; }
	for (int i = 0; i <= n + N; ++i) for (int lst = 0; lst < 3; ++lst) for (int mask = 0; mask < 4; ++mask) f[0][i][lst][mask] = inf;
	f[0][N][2][0] = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = -i + N; j <= i + N; ++j) for (int lst = 0; lst < 3; ++lst) for (int mask = 0; mask < 4; ++mask) f[i&1][j][lst][mask] = inf;
		for (int j = -(i - 1) + N; j <= (i - 1) + N; ++j) for (int lst = 0; lst < 3; ++lst) for (int mask = 0; mask < 4; ++mask) if (f[1 - (i&1)][j][lst][mask] != inf) {
			// use
			if (a[i] != 2) mnm(f[i&1][j][lst][mask], f[1 - (i&1)][j][lst][mask] + 1);
			if (a[i] == 2 && j > 0) mnm(f[i&1][j-1][lst][mask], f[1 - (i&1)][j][lst][mask] + 1);
			// not use
			int nmask = mask; if (a[i] < 2) nmask |= (1 << a[i]);
			mnm(f[i&1][j + (a[i] == 1 - lst)][a[i]][nmask], f[1 - (i&1)][j][lst][mask]);
		}
 	}

 	int ans = inf;
 	for (int j = -n + N; j <= N; ++j) for (int lst = 0; lst < 3; ++lst) ans = min(ans, f[n&1][j][lst][3]);
 	ans = min(ans, check());
 	for (int i = 1; i <= n; ++i) if (a[i] < 2) a[i] ^= 1;
 	ans = min(ans, check());

  	if (ans == inf) printf("-1\n"); else printf("%d\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt; while(tt--) solve();
}