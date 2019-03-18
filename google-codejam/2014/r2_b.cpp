#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, a[N];
int ans;

int solve() {
	cin >> n;
	ans = 0;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) {
		int L = 0, R = 0;
		for (int j = 1; j < i; ++j) if (a[j] > a[i]) ++L;
		for (int j = i + 1; j <= n; ++j) if (a[j] > a[i]) ++R;
		ans += min(L, R);
 	}
 	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: %d\n", i, solve());
	}
}