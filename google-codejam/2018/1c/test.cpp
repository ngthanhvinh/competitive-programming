#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt = 10;
	cout << tt << endl;
	while(tt--) {
		int n = rand() % 20 + 1;
		cout << n << endl;
		for (int i = 1; i <= n; ++i) cout << rand() % 100 + 1 << ' '; cout << endl;
	}
}