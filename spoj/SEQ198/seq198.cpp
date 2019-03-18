#include <bits/stdc++.h>
using namespace std;

const int MAX = 2010;

int n, m, a[MAX], f[MAX][1<<10], cnt[MAX];

void backt() {
	int ans = 1e9;
	for (int mask = 0; mask < (1<<n); mask++) {
		bool check = 1;
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if ((mask & (1<<i)) && (mask & (1<<j)) && (a[j+1] - a[i+1] == 1 || a[j + 1] - a[i + 1] == 8 || a[j + 1] - a[i + 1] == 9)) check = 0;
				if (!check) break;
			}
			if (!check) break;
		}
		if (!check) continue;
		int res = 0;
		for (int i = 0; i < n; i++) if (!(mask & (1 << i))) res += cnt[i + 1];
		ans = min(ans, res);
	}
	printf("%d\n", ans);
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	int cur_val = -1;
	for (int i = 1; i <= n; i++) { 
		if (a[i] != cur_val) { cur_val = a[i]; ++m; a[m] = cur_val; cnt[m] = 1; }  
		else cnt[m]++;
	}
	n = m;
	if (n < 10) return backt(), 0;
	for (int i = 0; i <= n; i++) for (int j = 0; j < (1<<10); j++) f[i][j] = 1e9;
	for (int mask = 0; mask < (1<<10); mask++) {
		bool check = 1;
		for (int i = 0; i <= 8; i++) if (mask & (1 << i)) {
			for (int j = i + 1; j <= 9; j++) if (mask & (1<<j)) {
				if (a[j + 1] - a[i + 1] == 1 || a[j + 1] - a[i + 1] == 8 || a[j + 1] - a[i + 1] == 9) check = 0;
				if (!check) break;
			} 
			if (!check) break;
		}
		if (!check) continue;
		int res = 0;
		for (int i = 0; i <= 9; i++) if (!(mask & (1 << i))) res += cnt[i+1]; 
		f[10][mask] = min(f[10][mask], res);
	}

	for (int i = 10; i < n; i++) for (int mask = 0; mask < (1 << 10); mask++) {
		// now we have f[i][mask] --> calculate f[i + 1][mask']
		int Mask1 = (mask>>1), Mask2 = (mask>>1) ^ (1<<9);
		f[i + 1][Mask1] = min(f[i + 1][Mask1], f[i][mask] + cnt[i + 1]);
		bool check = 1;
		for (int j = 0; j <= 8; j++) if (mask & (1 << (9 - j))) 
			if (a[i + 1] - a[i - j] == 1 || a[i + 1] - a[i - j] == 8 || a[i + 1] - a[i - j] == 9) { check = 0; break; }
		if (!check) continue;
		f[i + 1][Mask2] = min(f[i + 1][Mask2], f[i][mask]);
	}
	int ans = 1e9;
	for (int mask = 0; mask < (1<<10); mask++) {
		ans = min(ans, f[n][mask]);
	}
	printf("%d\n", ans);
}