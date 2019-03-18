#include <bits/stdc++.h>
using namespace std;

const int N = 26;

int n, a[N];

void solve() {
	cin >> n;

	int sum = 0;
	for (int i = 0; i < n; ++i) cin >> a[i], sum += a[i];
	if (sum % 2 == 1) {
		int p = 0;
		for (int i = 0; i < n; ++i) if (a[i] > a[p]) p = i;
		a[p]--;
		printf("%c ", (char)(p + 'A'));
	}

	priority_queue < pair<int,int> > pq;
	for (int i = 0; i < n; ++i) if (a[i]) pq.push(make_pair(a[i], i));

	while(!pq.empty()) {
		int best1 = pq.top().second; pq.pop();
		int best2 = pq.top().second; pq.pop();
		--a[best1];
		--a[best2];
		if (a[best1]) pq.push(make_pair(a[best1], best1));
		if (a[best2]) pq.push(make_pair(a[best2], best2));
		printf("%c%c ", (char)(best1 + 'A'), (char)(best2 + 'A'));
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve();
		printf("\n");
	}
}