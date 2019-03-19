#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int MAX = 20005;
const int inf = 1e9;

int n, k;
int a[N], b[N], c[N];
int f[N][MAX];
int t[N][MAX];
deque<int> q[MAX];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> b[i];
	for (int i = 1; i <= n; ++i) cin >> c[i];
	cin >> k;
	
	for (int i = 0; i <= n; ++i) for (int j = 0; j <= k; ++j) f[i][j] = inf;

	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		int bi = b[i], ci = c[i];
		for (int j = 0; j < bi; ++j) q[j] = deque<int>();
		for (int j = 0; j <= k; ++j) {
			int md = j % bi;
			int lim = 0;
			if (j >= 1LL * bi * ci) lim = j - bi * ci;

			while(!q[md].empty() && q[md].front() < lim) q[md].pop_front();
			while(!q[md].empty() && f[i-1][q[md].back()] - q[md].back() / bi > f[i-1][j] - j / bi) q[md].pop_back();
			q[md].push_back(j);
			f[i][j] = j / bi + f[i-1][q[md].front()] - q[md].front() / bi;
			t[i][j] = (j - q[md].front()) / bi;
		}
	}

	printf("%d\n", f[n][k]);

	int cur = n;
	while(cur > 0) {
		a[cur] = t[cur][k];
		k -= a[cur] * b[cur];
		--cur;
	}

	for (int i = 1; i <= n; ++i) printf("%d ", a[i]); printf("\n");
}