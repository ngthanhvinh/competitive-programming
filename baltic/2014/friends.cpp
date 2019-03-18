#include <bits/stdc++.h>
using namespace std;

void out() { printf("NOT POSSIBLE\n"); exit(0); }

const int N = 2000005;
const int md = 1e9 + 123;
const int BASE = 27;

string s;
int n;
int ans, pos;
int H[N];
int pw[N];
vector < pair<int,int> > A;

int get(int l, int r) {
	if (l > r) return 0;
	int res = (H[r] - (1LL * H[l-1] * pw[r - l + 1] % md)) % md;
	if (res < 0) res += md; return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> s; s = ' ' + s;
	if (n % 2 == 0) out();
	pw[0] = 1; for (int i = 1; i < N; ++i) pw[i] = 1LL * pw[i-1] * BASE % md;
	for (int i = 1; i <= n; ++i) H[i] = (1LL * H[i-1] * BASE + s[i] - 'A') % md;

	int sz = n / 2;

	for (int i = 1; i <= n; ++i) {
		int H0 = 0, H1 = 0;
		if (i <= sz + 1) {
			H0 = (1LL * get(1, i - 1) * pw[sz - i + 1] % md + get(i + 1, sz + 1)) % md;
			H1 = get(sz + 2, n);
		} else {
			H0 = get(1, sz);
			H1 = (1LL * get(sz + 1, i - 1) * pw[sz * 2 - i + 1] % md + get(i + 1, n)) % md;
		}
		if (H0 == H1) A.push_back(make_pair(H0, i));
	}
	sort(A.begin(), A.end());
	if (A.empty()) out();
	else {
		for (int i = 0; i < (int)A.size(); ++i) if (A[i].first != A[0].first) return printf("NOT UNIQUE\n"), 0;
		int pos = A[0].second;

		if (pos <= sz + 1) for (int i = sz + 2; i <= n; ++i) printf("%c", s[i]);
		else for (int i = 1; i <= sz; ++i) printf("%c", s[i]);
		printf("\n");
	}
}