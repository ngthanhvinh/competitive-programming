#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int md = 1e9 + 7;

int n;
int a[N], b[N];
vector<int> z;
int len[N * 2], sz;
int clen[N * 2][N], c[N][N];
int f[N], sum[N], g[N];

int pw(int a, int b) {
	int res = 1;
	while(b) {
		if (b & 1) res = 1LL * res * a % md; 
		a = 1LL * a * a % md;
		b >>= 1;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i]; ++b[i];
		z.push_back(a[i]); z.push_back(b[i]);
	}
	sort(z.begin(), z.end());
	z.resize(distance(z.begin(), unique(z.begin(), z.end())));

	for (int i = 0; i < (int)z.size() - 1; ++i) {
		len[++sz] = z[i + 1] - z[i];
		clen[sz][0] = 1;
		for (int j = 1; j <= n; ++j) {
			if (j > len[sz]) continue;
			clen[sz][j] = 1LL * clen[sz][j-1] * (len[sz] - j + 1) % md;
			clen[sz][j] = 1LL * clen[sz][j] * pw(j, md - 2) % md;
		}
	}

	for (int i = 0; i <= n; ++i) c[i][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) c[i][j] = (c[i-1][j-1] + c[i-1][j]) % md;
	}

	for (int k = 1; k <= sz; ++k) {
		vector<int> cand;
		for (int i = 1; i <= n; ++i) {
			if (a[i] <= z[k - 1] && z[k] <= b[i]) cand.push_back(i);
		}
		int s = cand.size();

		for (int i = 0; i < s; ++i) {
			if (i == 0) {
				for (int gap = 0; gap <= s; ++gap) g[gap] = 0;
				g[1] = len[k];
				for (int j = 1; j < s; ++j) {
					int gap = j - i + 1;
					for (int choose = 2; choose <= gap && choose <= len[k]; ++choose) {
						g[gap] = (g[gap] + 1LL * clen[k][choose] * c[gap-2][choose-2]) % md;
					}
				}
			}

			for (int j = i; j < s; ++j) {
				f[j] = (f[j] + 1LL * g[j - i + 1] * (sum[cand[i]-1] + 1)) % md;
			}
		}

		int cur = 0, pt = 0;
		for (int i = 1; i <= n; ++i) {
			while(pt < s && cand[pt] == i) cur = (cur + f[pt]) % md, f[pt] = 0, ++pt;
			sum[i] = (sum[i] + cur) % md;
		}
	}

	cout << sum[n] << '\n';
}