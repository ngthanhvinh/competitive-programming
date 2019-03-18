#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	srand(time(NULL));
	int n = 100, m = 3000;
	cout << n << ' ' << m << ' ' << rand() % 15464756 + 1 << ' ' << rand() % n << ' ' << 1 << endl;
	m -= (n - 1);
	for (int i = 0; i < m; ++i) cout << rand() % n << ' ' << rand() % n << endl;
	for (int i = 1; i < n; ++i) cout << i << ' ' << rand() % i << endl;
}