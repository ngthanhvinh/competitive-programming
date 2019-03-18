#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, a[N], b[N], res[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	while(tt--) {
		cin >> n; 
		vector<int> pos;
		for (int i = 1; i <= n; ++i) cin >> a[i], pos.push_back(i);
		sort(pos.begin(), pos.end(), [&](int x, int y) {
			return a[x] < a[y];
		});

		int ans = -1;
		if (n < 5) {
			vector< pair<int,int> > A;
			for (int i = 1; i <= n; ++i) A.push_back(make_pair(a[i],i));
			sort(A.begin(), A.end());

			do { // backtrack with n <= 4
				int cur = 0;
				for (int i = 0; i < A.size(); ++i) b[i + 1] = A[i].first;
				for (int i = 1; i <= n; ++i) cur += b[i] != a[i];
				if (ans < cur) {
					ans = cur;
					for (int i = 1; i <= n; ++i) res[i] = b[i];
				}
			} while(next_permutation(A.begin(), A.end()));
			printf("%d\n", ans);
			for (int i = 1; i <= n; ++i) printf("%d ", res[i]); printf("\n");
			continue;
		}

		ans = 0;
		for (int i = 0; i < n; ++i) b[pos[(i + 2) % n]] = a[pos[i]];
		for (int i = 1; i <= n; ++i) ans += b[i] != a[i];
		printf("%d\n", ans);
		for (int i = 1; i <= n; ++i) {
			printf("%d ", b[i]);
		}
		printf("\n");
	}
}