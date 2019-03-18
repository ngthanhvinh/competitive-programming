#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int n, A, B;
long long a[N];
long long OR;

// ------------------------------------------------
bool dp[110][110];
bool check(int x) {
	memset(dp, 0, sizeof dp);
	long long t = (OR >> x);
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int gr = 1; gr <= B; ++gr) {
			for (int j = 0; j < i; ++j) {
				long long cur = ((a[i] - a[j]) >> x);
				if ((t & cur) == cur) dp[i][gr] = max(dp[i][gr], dp[j][gr-1]);
			}
		}
	}

	for (int gr = A; gr <= B; ++gr) if (dp[n][gr]) return true;
	return false;
}

void solve() {
	for (int i = 49; i >= 0; --i) {
		if (!check(i)) {
			OR |= (1LL << i);
		}
	}
	cout << OR << '\n';
}

// ------------------------------------------------
int _dp[N];

int calc(int x) {
	for (int i = 1; i <= n; ++i) _dp[i] = n + 1;
	long long t = (OR >> x);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			long long cur = ((a[i] - a[j]) >> x);
			if ((t & cur) == cur) _dp[i] = min(_dp[i], _dp[j] + 1);
		}
	}
	return _dp[n];
}

void _solve() {
	for (int i = 49; i >= 0; --i) {
		if (calc(i) > B) OR |= (1LL << i);
	}
	cout << OR << '\n';
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> A >> B;
	for (int i = 1; i <= n; ++i) cin >> a[i], a[i] += a[i-1];
	if (A != 1) solve();
	else _solve();
}