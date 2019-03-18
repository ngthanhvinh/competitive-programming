#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int INF = 1e9;

int n, m;
int H[N], W, X, Y, Z;
int A[N], B[N], U[N], D[N];
double L[N], R[N];
int S[N], T[N];

bool check(double k) {
	for (int i = 1; i <= n; ++i) {
		L[i] = max(0.0, H[i] - k);
		R[i] = H[i] + k;
		//cerr << "#" << i << ' ' << L[i] << ' ' << R[i] << endl;
	}

	for (int i = 2; i <= n; ++i) {
		L[i] = max(L[i], L[i - 1] - S[i - 1]);
		R[i] = min(R[i], R[i - 1] + T[i - 1]);
		if (L[i] > R[i]) {
			return false;
		}
	}

	return true;
}

void solve() {
	cin >> n >> m;
	cin >> H[1] >> H[2] >> W >> X >> Y >> Z;
	for (int i = 3; i <= n; ++i) {
		H[i] = (1LL * W * H[i - 2] + 1LL * X * H[i - 1] + Y) % Z;
	}

	for (int i = 1; i <= n - 1; ++i) {
		S[i] = INF;
		T[i] = INF;
		// newH[i] - S[i] <= newH[i + 1] <= newH[i] + T[i]
	}

	for (int i = 1; i <= m; ++i) {
		cin >> A[i] >> B[i] >> U[i] >> D[i];
		for (int j = A[i]; j < B[i]; ++j) {
			S[j] = min(S[j], D[i]);
			T[j] = min(T[j], U[i]);
		}
		for (int j = B[i]; j < A[i]; ++j) {
			S[j] = min(S[j], U[i]);
			T[j] = min(T[j], D[i]);
		}
	}

	double low = 0.0, high = 10000000.0;
	for (int i = 0; i < 70; ++i) {
		double mid = (low + high) * 0.5;
		if (check(mid)) high = mid;
		else low = mid;
	}

	//cout << check(3.1) << endl;

	cout << setprecision(6) << fixed << low << endl;
}

int main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;
	for (int itest = 1; itest <= ntest; ++itest) {
		cout << "Case #" << itest << ": ";
		solve();
	}
}