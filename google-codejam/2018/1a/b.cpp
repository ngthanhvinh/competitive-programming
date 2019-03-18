#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int nrobot, nbit, ncashier;
long long can[N];
int M[N], S[N], P[N];

long long calc(long long x) {
	for (int i = 1; i <= ncashier; ++i) {
		can[i] = max(0LL, (x - P[i]) / S[i]);
		can[i] = min(can[i], (long long)M[i]);
	}
	sort(can + 1, can + ncashier + 1, greater<long long>());

	long long ret = 0;
	for (int i = 1; i <= nrobot; ++i) {
		ret += can[i];
		if (ret >= nbit) return true;
	}

	return false;
}

void solve() {
	cin >> nrobot >> nbit >> ncashier;
	for (int i = 1; i <= ncashier; ++i) {
		cin >> M[i] >> S[i] >> P[i];
	}
	
	long long low = 0, high = 2e18;
	while(low < high) {
		long long mid = ((low + high) >> 1);
		if (calc(mid)) {
			high = mid;
		} else {
			low = mid + 1;
		}
	}

	printf("%lld\n", low);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}