#include <bits/stdc++.h>
using namespace std;

int main() {
	vector <int> p(5);
	for (int i = 0; i < 5; ++i) p[i] = i;

	do {
		//system("sleep 1");
		freopen("sorting.in", "w", stdout);
		cout << 5 << endl;
		for (int i = 0; i < 5; ++i) cout << p[i] << ' '; cout << endl;
		for (int i = 0; i < 5; ++i) cerr << p[i] << ' '; cerr << endl;
		cout << 25 << endl;
		for (int j = 0; j < 25; ++j) {
			cout << 0 << ' ' << 0 << endl;
		}
		system("./sorting < sorting.in > sorting.out");
	} while(next_permutation(p.begin(), p.end()));
}