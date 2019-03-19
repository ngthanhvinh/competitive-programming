#include <bits/stdc++.h>
using namespace std;

int ans;
int smin, smax;
int wmin, wmax;
int MAGIC;

void build(int l, int r, vector< pair<int,int> > &seg) {
	for (int val = MAGIC; val >= 0; --val) {
		int kr = val ? l / val : 1e9, kl = (l + val + (l % (val + 1) == 0)) / (val + 1);
		int lim = r / (val + 1);
		if (min(lim, kr) < kl) continue;
		seg.push_back(make_pair(kl, +1));
		seg.push_back(make_pair(min(lim, kr), -1)); 
		//cerr << kl << ' ' << min(lim, kr) << ' ' << val << endl;
	}
}

void solve() {
	cin >> smin >> smax; --smin;
	cin >> wmin >> wmax; --wmin;
	ans = 1;
	MAGIC = max(sqrt(smin), sqrt(wmin));
	// with k <= MAGIC
	for (int k = 1; k <= MAGIC; ++k) {
		int s = smax / k - smin / k;
		int w = wmax / k - wmin / k;
		if (s > 0 && w > 0) ans = k;
	}

	// with k >= MAGIC
	vector< pair<int,int> > S, W;
	build(smin, smax, S);
	build(wmin, wmax, W);

	int x = 0;
	int ptS = 0, ptW = 0, cntS = 0, cntW = 0;

	while(ptS < S.size() && ptW < W.size()) {
		x = min(S[ptS].first, W[ptW].first);
		if (S[ptS].first == x && S[ptS].second == +1) cntS++;
		if (W[ptW].first == x && W[ptW].second == +1) cntW++;
		if (cntS > 0 && cntW > 0) ans = max(ans, x);
		if (S[ptS].first == x && S[ptS].second == -1) cntS--;
		if (W[ptW].first == x && W[ptW].second == -1) cntW--;

		if (S[ptS].first == x) ++ptS;
		if (W[ptW].first == x) ++ptW;
	}

	printf("%d\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	while(tt--) {
		solve();
	}
}