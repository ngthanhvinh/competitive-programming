// http://wcipeg.com/problem/noi14p1
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, MAX;
string s[N];
int a[N];
int ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> MAX;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i] >> a[i];
	}

	bool smaller = false;
	for (int bit = 30; bit >= 0; --bit) {
		int mx = smaller ? 1 : (MAX >> bit & 1);
		int best = -1, best_res = -1;

		for (int cur = 0; cur <= mx; ++cur) {
			int tmp = cur;
			for (int i = 1; i <= n; ++i) {
				if (s[i][0] == 'A') tmp &= (a[i] >> bit & 1); // AND
				if (s[i][0] == 'O') tmp |= (a[i] >> bit & 1); // OR
				if (s[i][0] == 'X') tmp ^= (a[i] >> bit & 1); // XOR
			}
			if (tmp > best_res) {
				best_res = tmp;
				best = cur;
			}
		}

		assert(best != -1);
		if (best < mx) smaller = true;
		ans = 2 * ans + best_res;
	}

	printf("%d\n", ans);
}