#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, t[N];
long long k;

long long get(int x) {
	// A / B < x / n
	for (int i = 1; i <= n; ++i) t[i] = 0;

	long long ret = 0;
	for (int i = 2; i <= n; ++i) {
		int lim = (1LL * x * i - 1) / n;
		t[i] = lim - t[i];
		ret += t[i];
		for (int j = i + i; j <= n; j += i) t[j] += t[i];
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;

	int l = 1, r = n;
	while(l < r) {
		int mid = ((l + r) >> 1);
		if (get(mid) >= k) r = mid; else l = mid + 1;
	}

	// (l - 1) / n <= A / B < l / n
	k -= get(l - 1);

	vector< pair<int,int> > frac;
	for (int i = 2; i <= n; ++i) {
		int low = (1LL * (l - 1) * i + n - 1) / n;
		int high = (1LL * l * i - 1) / n;
		if (low <= high && __gcd(low, i) == 1) frac.push_back(make_pair(low, i));
	}

	sort(frac.begin(), frac.end(), [&](pair<int,int> p, pair<int,int> q) {
		return 1LL * p.first * q.second < 1LL * q.first * p.second;
	});

	printf("%d %d\n", frac[k - 1].first, frac[k - 1].second);
}