#include <bits/stdc++.h>
using namespace std;

const int N = 205;

int nrow, ncol;
int a[N], pos[N];
char res[N][N];

void solve() {
	cin >> ncol;
	for (int i = 1; i <= ncol; ++i) {
		cin >> a[i];
	}	
	int cur = 1;
	for (int i = 1; i <= ncol; ++i) {
		while(a[i] > 0) {
			--a[i];
			pos[cur] = i;
			++cur;
		}
	}

	nrow = 0;
	for (int i = 1; i <= ncol; ++i) {
		nrow = max(nrow, abs(pos[i] - i));
	}

	if (pos[1] != 1 || pos[ncol] != ncol) {
		cout << "IMPOSSIBLE\n"; return;
	}

	for (int i = 1; i <= nrow + 1; ++i) {
		for (int j = 1; j <= ncol; ++j) {
			res[i][j] = '.';
		}
	}

	for (int i = 1; i <= ncol; ++i) {
		int to = pos[i];
		for (int j = i, k = 1; j < to; ++j, ++k) {
			res[k][j] = '\\';
		}
		for (int j = i, k = 1; j > to; --j, ++k) {
			res[k][j] = '/';
		}
	}

	cout << nrow + 1 << '\n';
	for (int i = 1; i <= nrow + 1; ++i) {
		for (int j = 1; j <= ncol; ++j) {
			cout << res[i][j];
		}
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;

	for (int itest = 1; itest <= ntest; ++itest) {
		cout << "Case #" << itest << ": ";
		solve(); 
	}
}