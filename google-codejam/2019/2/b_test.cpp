#include <bits/stdc++.h>
using namespace std;

int a[15], b[15];

int main() {
	srand(time(NULL));
	cout << 1 << endl;
	int n = 10;
	for (int i = 1; i <= n; ++i) {
		a[i] = rand() % 100 + 1;
	}
	for (int i = 1; i <= n; ++i) {
		b[i] = rand() % 100 + 1;
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);

	for (int i = 1; i <= n; ++i) {
		cout << a[i] << ' ' << b[i] << endl;
	}
}