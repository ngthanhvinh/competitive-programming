#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 32;
	int w = 1024;
	int r = 320;
	cout << n << ' ' << w << ' ' << r << endl;

	vector <int> p(n);
	for (int i = 0; i < n; ++i) p[i] = i;
	random_shuffle(p.begin(), p.end());

	for (int i = 0; i < n; ++i) {
		cout << p[i] << ' ';
	}
	cout << endl;
}