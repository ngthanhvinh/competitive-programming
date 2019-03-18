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
	freopen("input.txt", "r", stdin);
	freopen("ans.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	int cur_val = -1;
	for (int i = 1; i <= n; i++) { 
		if (a[i] != cur_val) { cur_val = a[i]; ++m; a[m] = cur_val; cnt[m] = 1; }  
		else cnt[m]++;
	}
	n = m;
	backt();
}