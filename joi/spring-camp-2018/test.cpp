#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	srand(time(NULL));

	int n = 200;
	cout << n << endl;
	for (int i = 1; i <= n; ++i) cout << rand() % 1000000 + 1 << endl;
}