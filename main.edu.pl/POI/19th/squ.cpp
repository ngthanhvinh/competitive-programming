#include <bits/stdc++.h>
using namespace std;

const int N = 310;

int n, a[N * N];
int b[N];

vector < vector<int> > ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	int tot = n * (n - 1) / 2;
	for (int i = 1; i <= n * (n - 1) / 2; ++i) cin >> a[i];
	sort(a + 1, a + tot + 1);
	for (int i = 1; i <= n; ++i) cerr << a[i] << ' '; cerr << endl;

	for (int i = 3; i <= min(tot, n); ++i) {
		int sum = a[i] + a[1] + a[2];
		if (sum & 1) continue;
		sum >>= 1;
		b[1] = sum - a[i], b[2] = sum - a[2], b[3] = sum - a[1];
		int cur = 3;
		for (int j = 3; j <= min(tot, n); ++j) if (j != i) b[++cur] = a[j] - b[1];

		bool valid = 1;
		for (int j = 1; j < n; ++j) if (b[j] >= b[j + 1]) valid = 0;
		for (int j = 1; j <= n; ++j) if (b[j] <= 0) valid = 0;
		

		vector <int> s;
		for (int j = 1; j < n; ++j) for (int k = j + 1; k <= n; ++k) s.push_back(b[j] + b[k]);
		sort(s.begin(), s.end());
		for (int j = 0; j < tot; ++j) if (s[j] != a[j + 1]) { valid = 0; break; }

		if (valid) {
			vector <int> vec;
			for (int j = 1; j <= n; ++j) vec.push_back(b[j]);
			ans.push_back(vec);
		}
	}
	sort(ans.begin(), ans.end()); ans.resize(distance(ans.begin(), unique(ans.begin(), ans.end())));
	printf("%d\n", (int)ans.size());
	for (int i = 0; i < ans.size(); ++i) {
		for (int j = 0; j < ans[i].size(); ++j) printf("%d ", ans[i][j]);
		printf("\n");
	}
}
