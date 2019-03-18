#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
int a[N], del[N];
int trace[N];
bool dp[N][5];
vector <int> vres;
vector <int> vec[N];

void solve() {
	cin >> n >> q;
	for (int i = 1; i <= q; ++i) cin >> a[i];
	a[q + 1] = n + 1;
	
	vres.clear();

	for (int i = 1; i <= q + 1; ++i) {
		vec[i].clear();
		if (a[i] - a[i - 1] - 1 <= 4) {
			for (int j = a[i - 1] + 1; j < a[i]; ++j) vec[i].push_back(j);
			del[i] = vec[i].size();
			continue;
		}

		int last = a[i - 1] + 1;
		int cur = a[i - 1] + 2;
		while(a[i] - cur + 1 > 4) {
			vres.push_back(cur);
			last = cur;
			cur += 2;
		}
		vec[i].push_back(last);
		for (int j = cur; j < a[i]; ++j) vec[i].push_back(j);
		del[i] = vec[i].size();
	}

	// dp
	for (int i = 1; i <= n; ++i) {
		for (int last = 0; last <= 4; ++last) {
			dp[i][last] = 0;
		}
	}
	dp[0][0] = 1;
	for (int i = 0; i <= q; ++i) {
		for (int last = 0; last <= 4; ++last) {
			if (!dp[i][last]) continue;
			for (int use = del[i + 1]; use >= 0; ) {
				int rem = use - last;
				if (rem < 0) break;
				dp[i + 1][rem] = 1;

				if (use > 2) use -= 2; else break;
			}
		}
	}
	
	// trace
	if (!dp[q + 1][0]) {
		printf("-1\n");
		return;
	}
	int pos = q + 1, rem = 0;
	while(pos > 0) {
		for (int use = del[pos]; use >= 0; ) {
			int last = use - rem;
			if (last >= 0 && dp[pos - 1][last]) {
				trace[--pos] = last;
				rem = last;
				break;
			}

			if (use > 2) use -= 2; else break;
		}
	}

	for (int i = 1; i <= q; ++i) {
		del[i] -= trace[i];
		del[i + 1] -= trace[i];
		if (del[i] >= 2 && vec[i].size() > 2) {
			vres.push_back(vec[i][1]);
			vec[i].erase(vec[i].begin() + 2);
			vec[i].erase(vec[i].begin());
		}
	}
	for (int i = 1; i <= q; ++i) {
		while(trace[i]-- > 0) {
			vres.push_back(a[i]);
		}
	}

	// answer
	printf("%d\n", vres.size());
	for (int &i : vres) printf("%d ", i);
	printf("\n");
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int tt; cin >> tt;
	while(tt--) {
		solve();
	}
}