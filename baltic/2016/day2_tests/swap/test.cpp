#include <bits/stdc++.h>
using namespace std;

int a[11];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int n = 10;
	for (int i = 1; i <= n; ++i) a[i] = i;

	while(true) {
		freopen("in", "w", stdout);
		random_shuffle(a + 1, a + n + 1);
		cout << n << endl;
		for (int i = 1; i <= n; ++i) cout << a[i] << ' '; cout << endl;

		system("./swap < in > out");
		system("./swap_stress < in > ans");
		if (system("diff ans out") != 0) {
			cerr << "Wrong Answer!\n";
			return 0;
		}
	}
}