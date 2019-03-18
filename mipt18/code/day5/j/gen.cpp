#include <bits/stdc++.h>
using namespace std;

int a[50];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int n = 5;
	for (int i = 1; i <= n; ++i) a[i] = i;

	int cnt = 0;
	do {
		++cnt;
		freopen("in", "w", stdout);
		cout << n << endl;
		for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
		cout << endl;

		system("./j < in > out");
		system("./j_sol < in > ans");

		ifstream fout("out");
		ifstream fans("ans");

		int out, ans;
		fout >> out;
		fans >> ans;

		if (out != ans) {
			cerr << "Wrong Answer\n";
			return 0;
		} else {
			cerr << "True\n";
		}
	} while(next_permutation(a + 1, a + n + 1));

	cerr << cnt << endl;
}