#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const double eps = 1e-9;

int n;
double V, X;
double R[N], C[N];

bool eq(double a, double b) { return abs(a - b) <= eps; }

void solve() {
	cin >> n >> V >> X; V *= X;
	for (int i = 1; i <= n; ++i) cin >> R[i] >> C[i], C[i] *= R[i];
	
	double T = 0.0;

	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) if (!eq(R[i] * C[j], R[j] * C[i])) {
			double sR = 0.0, sC = 0.0;
			for (int k = 1; k <= n; ++k) if (k != i && k != j) {
				sR += R[k];
				sC += C[k];
			}
			if (!eq(sR, 0.0)) {
				
			}
		}
	}
	return T;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		cout << setprecision(9) << fixed << solve() << endl;
	}
}