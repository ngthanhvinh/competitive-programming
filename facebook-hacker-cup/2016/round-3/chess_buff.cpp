#include <bits/stdc++.h>
using namespace std;

int n;
double W[2], L[2];
double f[110][2];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 0; i < 2; ++i) cin >> W[i];
	for (int i = 0; i < 2; ++i) cin >> L[i];

	f[1][0] = W[0], f[1][1] = W[1];
	for (int i = 2; i <= n; ++i) {
		for (int color = 0; color < 2; ++color) {
			f[i][color] = L[color] * max(f[i - 1][0], f[i - 1][1]) + (1.0 - L[color]) * min(f[i - 1][0], f[i - 1][1]);
			cerr << i << ' ' << color << ' ' << f[i][color] << endl;
		}
	}

	cout << f[n][0] << endl;
}