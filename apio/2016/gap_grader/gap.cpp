#include "gap.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n;
vector<long long> a;
long long s = 0, t = 2e18;
long long mn, mx;

long long solve1() {
	for (int i = 1; i <= (n + 1) / 2; ++i) {
		if (s <= t) MinMax(s, t, &mn, &mx);
		a.push_back(mn);
		a.push_back(mx);
		s = mn + 1, t = mx - 1;
	}
}

long long solve2() {
	MinMax(0, 2e18, &s, &t);
	long long gap = (t - s + n - 2) / (n - 1);
	for (long long i = s; i <= t; i += gap + 1) {
		MinMax(i, i + gap, &mn, &mx);
		a.push_back(mn);
		a.push_back(mx);
	}
}

long long findGap(int T, int _N) {
	n = _N;
	if (T == 1) solve1();
	else solve2();

	long long ans = 0;
	sort(a.begin(), a.end());
	for (int i = 0; i < a.size()-1; ++i) {
		ans = max(ans, a[i+1] - a[i]);
	}
	return ans;
}
