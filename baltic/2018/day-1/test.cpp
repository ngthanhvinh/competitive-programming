#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	freopen("in", "w", stdout);
	int N = 100, M = 1, K = 1, Q = 35;
	cout << N << ' ' << M << ' ' << K << ' ' << Q << endl;
	
	int mid = rand() % N + 1;
	for (int i = 1; i <= N; ++i) {
		if (i == mid) cout << (int)1e9 << ' ';
		else cout << 1 << ' ';
	}
	cout << endl;
}