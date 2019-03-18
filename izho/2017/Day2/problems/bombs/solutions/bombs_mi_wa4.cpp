#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <queue>

#define mp make_pair
#define pb push_back


typedef long long ll;
typedef long double ld;

using namespace std;

const int MX = 2510;

int pr[MX][MX];
char s[MX][MX];
int gg[MX][MX];
int n, m;

int get(int x1, int y1, int x2, int y2) {
	x2 = min(x2, n);
	x1 = max(0, x1);
	y2 = min(y2, m);
	y1 = max(0, y1);
	return pr[x2][y2] - pr[x1][y2] - pr[x2][y1] + pr[x1][y1];
}

int check(int h, int w) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '0')
				continue;
			int fl1 = 0, fl2 = 0, fl3 = 0, fl4 = 0;
			if (i == 0 || s[i - 1][j] == '0')
				fl1 = 1;
			if (j == 0 || s[i][j - 1] == '0')
				fl2 = 1;
			if (i == n - 1 || s[i + 1][j] == '0')
				fl3 = 1;
			if (j == m - 1 || s[i][j + 1] == '0')
				fl4 = 1;
			if (fl1 && fl2)
				if (get(i, j, i + h, j + w) != h * w)
					return 0;
			if (fl2 && fl3)
				if (get(i - h + 1, j, i + 1, j + w) != h * w)
					return 0;
			if (fl3 && fl4)
				if (get(i - h + 1, j - w + 1, i + 1, j + 1) != h * w)
					return 0;
			if (fl4 && fl1)
				if (get(i, j - w + 1, i + h, j + 1) != h * w)
					return 0;
		}
	}
	return 1;
}

int main() {
      freopen("bomb.in","r",stdin);
  freopen("bomb.out","w",stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf(" %s", s[i]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			pr[i + 1][j + 1] = pr[i + 1][j] + pr[i][j + 1] + (s[i][j] == '1' ? 1 : 0) - pr[i][j];
	int mh = 0;
	int mw = 0;
	int mxh = n;
	int mxw = m;
	for (int i = 0; i < n; ++i) {
		int cnt = 0;
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '1')
				++cnt;
			if (s[i][j] == '1' && (j == m - 1 || s[i][j + 1] == '0')) {
				mxw = min(mxw, cnt);
				cnt = 0;
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		int cnt = 0;
		for (int j = 0; j < n; ++j) {
			if (s[j][i] == '1')
				++cnt;
			if (s[j][i] == '1' && (j == n - 1 || s[j + 1][i] == '0')) {
				mxh = min(mxh, cnt);
				cnt = 0;
			}
		}
	}
	int lst = mxw;
	for (int h = 1; h <= mxh; ++h) {
		while (lst > 0 && !check(h, lst))
			--lst;
		if (h * lst > mh * mw)
			mh = h, mw = lst;
	}
	cout << mh * mw << "\n";
	return 0;
}


