#include <bits/stdc++.h>
using namespace std;

const int MAX = 80000000;
const int N = 3005;

int n, m, L;
vector< pair<int,int> > A, B;
int mxA[N], mxB[N];
int f[N][N];

void solve() {
	cin >> n >> m >> L;
	A.clear(); B.clear();
	for (int i = 1; i <= n; ++i) {
		int x, y; cin >> x >> y; A.push_back(make_pair(x,y));
	}
	for (int i = 1; i <= m; ++i) {
		int x, y; cin >> x >> y; B.push_back(make_pair(x,y));
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	int ans = MAX;
	mxA[0] = -MAX;
	for (int i = 1; i <= A.size(); ++i) mxA[i] = max(mxA[i-1], A[i-1].second);
	mxB[0] = -MAX;
	for (int i = 1; i <= B.size(); ++i) mxB[i] = max(mxB[i-1], B[i-1].second);

	for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) f[i][j] = -MAX;
	f[0][0] = 0;
	for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) {
		if (f[i][j] == -MAX) continue;
		if (i < n) {
			int pr = lower_bound(A.begin(), A.end(), make_pair(f[i][j] + L, -MAX)) - A.begin();
			f[i + 1][j] = max(f[i + 1][j], mxA[pr]);
		}
		if (j < m) {
			int pr = lower_bound(B.begin(), B.end(), make_pair(f[i][j] + L, -MAX)) - B.begin();
			f[i][j + 1] = max(f[i][j + 1], mxB[pr]);
		}
	}

	for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) {
		if (f[i][j] > MAX - L) ans = min(ans, max(i,j));
	}

	if (ans == MAX) printf("Lunchtime\n"); else printf("%d\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}