#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("input.txt", "w", stdout); srand(time(NULL));
	ios_base::sync_with_stdio(false); cin.tie(0);
	int N = 10, M = 10, K = 3;
	cout << N << ' ' << M << ' ' << K << endl;
	for (int i = 2; i <= N; ++i) cout << i << ' ' << rand() % (i-1) + 1 << endl, --M;
	while(M--) {
		cout << rand() % N + 1 << ' ' << rand() % N + 1 << endl;
	}
}