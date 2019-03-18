#include <bits/stdc++.h>
using namespace std;

int n, a[32050];
int l, r;

int main() {
	ifstream fin("in");
	ifstream fout("out");

	fin >> n;
	for (int i = 1; i <= n; ++i) fin >> a[i];
	while(fout >> l >> r) {
		reverse(a + l, a + r + 1);
	}

	for (int i = 1; i <= n; ++i) cerr << a[i] << ' '; cerr << endl;
	for (int i = 2; i <= n; ++i) if (a[i] < a[i - 1]) return cerr << "WA!" << endl, 0; 

	cerr << "AC!\n";
}