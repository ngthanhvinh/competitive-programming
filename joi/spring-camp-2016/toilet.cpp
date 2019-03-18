#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

long long n;
int m;
long long ans = 0;
string s[N];
long long k[N];

int get_sum(string &s) {
	int ret = 0;
	for (int i = 0; i < s.size(); ++i) ret += (s[i] == 'M' ? +1 : -1);
	return ret;
}

long long max_suf(string &s, long long k) {
	long long ret = 0;
	int sum = get_sum(s), suf = 0;
	// find max(w * sum + suf) with 0 <= w < k
	long long w = (sum <= 0) ? 0 : (k - 1);
	for (int i = s.size() - 1; i >= 0; --i) {
		suf += (s[i] == 'M' ? +1 : -1);
		ret = max(ret, suf + 1LL * w * sum);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		cin >> s[i] >> k[i];
	}

	long long cur = 0;
	for (int i = m - 1; i >= 0; --i) {
		ans = max(ans, cur + max_suf(s[i], k[i]) - 1);
		cur += 1LL * get_sum(s[i]) * k[i];
	}

	if (cur > 1) cout << -1 << endl;
	else cout << ans << endl;
}