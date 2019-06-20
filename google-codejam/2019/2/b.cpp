#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef pair<int,int> ii;
const int N = 15;

int n, a[N], b[N];

void minimize(ii &R, ii tmp) {
	if (1LL * tmp.first * R.second < 1LL * R.first * tmp.second) {
		R = tmp;
	}
}
void maximize(ii &L, ii tmp) {
	if (1LL * tmp.first * L.second > 1LL * L.first * tmp.second) {
		L = tmp;
	}
}
void fix(ii &t) {
	int k = __gcd(t.first, t.second);
	if (!k) return;
	t.first /= k;
	t.second /= k;
}

bool check(long long val, ii &L, ii &R) {
	if (R.first <= 0) return false;
	long long mx = L.first ? (1LL * val * L.second - 1) / L.first : 1e18;
	long long mn = (1LL * val * R.second + R.first) / R.first;
	return mn <= mx;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i];
	}

	ii L = {0, 1}, R = {1e9 + 10, 1};
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {
			// i > j
			if (a[i] >= a[j] && b[i] >= b[j]) {
				continue;
			}
			if (a[j] >= a[i] && b[j] >= b[i]) {
				cout << "IMPOSSIBLE\n";
				return;
			}

			if (a[j] < a[i]) {
				maximize(L, ii(b[j] - b[i], a[i] - a[j]));
			} else {
				minimize(R, ii(b[i] - b[j], a[j] - a[i]));
			}
		}
	}

	fix(L);
	fix(R);

	if (1LL * R.first * L.second <= 1LL * L.first * R.second) {
		cout << "IMPOSSIBLE\n";
		return;
	}

	cerr << L.first << ' ' << L.second << endl;
	cerr << R.first << ' ' << R.second << endl;

	long long low = 1, high = 3e9;
	while(low < high) {
		long long mid = ((low + high) >> 1);
		cerr << mid << ' ' << check(mid, L, R) << endl;
		if (check(mid, L, R)) high = mid;
		else low = mid + 1;
	}

	if (check(low, L, R)) {
		long long mn = (1LL * low * R.second + R.first) / R.first;
		cout << low << ' ' << mn << endl;
	} else {
		cout << "IMPOSSIBLE\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(false);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		solve();
	}
}