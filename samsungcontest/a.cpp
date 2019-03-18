#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, k, a[N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest;
	cin >> ntest;

	for (int itest = 1; itest <= ntest; ++itest) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++i) cin >> a[i];
		sort(a + 1, a + n + 1);

		deque <int> dq;
		for (int i = 1; i <= n; ++i) {
			if (!dq.empty() && dq.front() < a[i] - k) {
				dq.pop_front();
				dq.push_back(a[i]);
			} else {
				dq.push_back(a[i]);
			}
		}

		printf("Case #%d\n%d\n", itest, dq.size());
	}
}