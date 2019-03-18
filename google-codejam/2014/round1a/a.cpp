#include <bits/stdc++.h>
using namespace std;

int N, L;
string s[155], S[155];
string t[155];

string calc(int x, int y) {
	string res = "";
	for (int i = 0; i < L; ++i) res += (char)('0' + (s[x][i] != t[y][i]));
	return res;
}

string change(string str, string q) {
	string res = "";
	for (int i = 0; i < L; ++i) {
		int c = str[i] - '0';
		if (q[i] == '0') res += (char)(c + '0'); else res += (char)((c ^ 1) + '0');
	}
	return res;
}

int solve() {
	cin >> N >> L;
	for (int i = 1; i <= N; ++i) cin >> s[i];
	for (int i = 1; i <= N; ++i) cin >> t[i];
	sort(t + 1, t + N + 1);
	
	int ans = 1e9;
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
		string res = calc(i, j);
		for (int k = 1; k <= N; ++k) S[k] = change(s[k], res);
		sort(S + 1, S + N + 1);
		bool check = true;

		for (int k = 1; k <= N; ++k) check &= (S[k] == t[k]);
		if (!check) break;

		int cnt = 0;
		for (int k = 0; k < L; ++k) cnt += res[k] == '1';
		ans = min(ans, cnt);
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		int r = solve();
		printf("Case #%d: ", i);
		if (r == 1e9) printf("NOT POSSIBLE\n"); else printf("%d\n", r);
	}
}