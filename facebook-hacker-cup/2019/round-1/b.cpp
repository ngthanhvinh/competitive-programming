#include <bits/stdc++.h>
using namespace std;

const int N = 1000020;
const int mod = 1e9 + 7;

void add(int &x, int y) {
	x += y; while (x >= mod) x -= mod;
}

int n, k;
int pw[N];
string s;

void solve() {
	cin >> n >> k >> s;

	int mn = 0;
	int last = 0;
	int res = 0;

	for (int i = n; i >= 1; --i) {
		int cur = last + (s[i - 1] == 'A' ? -1 : +1);
		if (cur - mn > k) {
			cur -= 2;
			add(res, pw[i]);
		}
		last = cur;
		mn = min(mn, last);
	}

	printf("%d\n", res);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	pw[0] = 1;
	for (int i = 1; i < N; ++i) {
		pw[i] = 2LL * pw[i - 1] % mod;
	}

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		printf("Case #%d: ", it);
		solve();
	}
}