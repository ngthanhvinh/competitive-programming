#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n;
string s;
int zl[N], zr[N];

void Z_algo(int z[]) {
	int L = 0, R = 0;
	for (int i = 1; i < n; ++i) {
		if (R < i) {
			L = i, R = i; while(R < n && s[R] == s[R - L]) ++R;
			z[i] = R - L; --R;
		} else {
			int k = i - L;
			if (z[k] < R - i + 1) z[i] = z[k];
			else {
				L = i; while(R < n && s[R] == s[R - L]) ++R;
				z[i] = R - L; --R;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> s;
	Z_algo(zl);
	reverse(s.begin(), s.end());
	Z_algo(zr);
	for (int i = 0; i < n / 2; ++i) swap(zr[i], zr[n - 1 - i]);

	for (int i = n / 2; i < n; ++i) {
		if (zl[i] + zr[n - i - 1] == n - i - 1) return cout << i << endl, 0;
	}

	cout << -1 << endl;
}