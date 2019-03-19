#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

char s[N];
int f[26][26], c[26][26], mn[26][26];
int n, ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> s[i];
	for (int i = 0; i < 26; ++i) for (int j = 0; j < 26; ++j) c[i][j] = 0, mn[i][j] = 1e9;

	for (int i = 1; i <= n; ++i) {
		int x = s[i] - 'a';
		for (int j = 0; j < 26; ++j) if (j != x) {
			f[x][j]++, f[j][x]--;
			ans = max(ans, f[x][j] - mn[x][j]);
		}
		for (int j = 0; j < 26; ++j) if (j != x) mn[j][x] = min(mn[j][x], c[j][x]), c[j][x] = min(c[j][x], f[j][x]), ans = max(ans, f[j][x] - c[j][x]);
	}

	cout << ans << endl;
}