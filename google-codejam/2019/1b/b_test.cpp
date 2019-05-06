#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, k;
int c[N], d[N];
int mxC[N][N], mxD[N][N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;

	for (int it = 1; it <= tt; ++it) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++i) cin >> c[i];
		for (int i = 1; i <= n; ++i) cin >> d[i];

		long long res = 0;
		for (int i = 1; i <= n; ++i) {
			mxC[i][i] = c[i];
			mxD[i][i] = d[i];
			for (int j = i; j <= n; ++j) {
				if (j > i) {
					mxC[i][j] = max(mxC[i][j - 1], c[j]);
					mxD[i][j] = max(mxD[i][j - 1], d[j]);
				}
				if (abs(mxC[i][j] - mxD[i][j]) <= k) {
					res++;
				}
			}
		}

		printf("Case #%d: %lld\n", it, res);
	}
}