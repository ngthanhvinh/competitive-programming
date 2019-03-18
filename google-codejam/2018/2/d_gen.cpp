#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n = 3, m = 4;
	cout << 10 << endl; // ntest

	for (int itest = 1; itest <= 10; ++itest) {
		cout << n << ' ' << m << endl;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int r = rand() % 2;
				cout << ((r == 0) ? 'B' : 'W');
			}
			cout << endl;
		}
	}
}