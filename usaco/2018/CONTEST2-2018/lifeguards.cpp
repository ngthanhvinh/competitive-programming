#include <bits/stdc++.h>
using namespace std;

int main() {
	scanf("%d%d", &nseg, &k);
	for (int i = 1; i <= nseg; ++i) scanf("%d%d", &tmp[i].first, &tmp[i].second);

	sort(tmp + 1, tmp + nseg + 1, [&](ii p, ii q) {
		return p.first < q.first || (p.first == q.first && p.second > q.second);
	});
		
	int maxr = 0;
	for (int i = 1; i <= nseg; ++i) {
		if (tmp[i].first >= maxr) {
			a[++n] = tmp[i]; maxr = tmp[i].second;
		} else {
			if (tmp[i].second <= maxr) {
				--k; continue;
			}
			a[++n] = tmp[i]; maxr = tmp[i].second;
		}
	}

	k = max(k, 0);

	// DP
	// dp[0]

	vector<int> Z;

	for (int i = 1; i <= n; ++i) Z.push_back(a[i].first), Z.push_back(a[i].second);
	sort(Z.begin(), Z.end());
	Z.erase(unique(Z.begin(), Z.end()), Z.end());

	for (int i = 1; i <= n; ++i) {
		int pl = lower_bound(Z.begin(), Z.end(), a[i].first) - Z.begin() + 1;
		int pr = lower_bound(Z.begin(), Z.end(), a[i].second) - Z.begin() + 1;
		segR[pr] = i;
	}

	for (int taken = 1; taken <= k; ++taken) {
		set <int> s;
		for (int i = 1; i <= n; ++i) {
			int pl = lower_bound(Z.begin(), Z.end(), a[i].first) - Z.begin() + 1;
			int pr = lower_bound(Z.begin(), Z.end(), a[i].second) - Z.begin() + 1;

			int j = segR[pr - 1];
			if (j) {
				s.erase(dp[pr - 1][taken - 1] - a[j].second);
				maxout = 
			}
		}
	}
}