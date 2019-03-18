#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int n, m, Div[N], Case;
vector <int> cnt(N, -1e9);
vector <int> a, SatisfiedValue;

void sieve() {
	Div[0] = Div[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!Div[i]) for (int j = i; j < N; j += i) Div[j] = i;
	}
}

void solve() {
	cin >> n >> m; 
	if (n == 0 && m == 0) { printf("Case %d: 0\n", ++Case); return; }
	if (n == 0 || m == 0) { printf("Case %d: 1\n", ++Case); return; }
	long long ans = 2;
	for (int i = 0; i < SatisfiedValue.size() && SatisfiedValue[i] <= min(n, m); ++i) {
		int x = SatisfiedValue[i];
		long long res = 1LL * (m / x) * (n / x);
		if (cnt[x] & 1) ans -= res;
		else ans += res;
	}
	printf("Case %d: %lld\n", ++Case, ans);
}

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0);
	sieve(); cnt[1] = 0; SatisfiedValue.push_back(1);
	for (int x = 1; x < N; x++) {
		int prNum = x / Div[x]; 
		if (x == prNum) continue;
		if (prNum % Div[x] != 0 && cnt[prNum] != -1e9) {
			cnt[x] = cnt[prNum] + 1;
			SatisfiedValue.push_back(x);
			//cout << x << ' ' << cnt[x] << "\n";
		}
	}
	int t; cin >> t;
	while(t--) solve();
}