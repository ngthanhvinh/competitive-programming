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
int gd[MX];
int n, m;

int get(int x1, int y1, int x2, int y2) {
	return pr[x2][y2] - pr[x1][y2] - pr[x2][y1] + pr[x1][y1];
}

int check(int h, int w) {
	for (int i = 0; i < m; ++i)
		gd[i] = 0;
	for (int i = 0; i < n; ++i) {
		int lst = 0;
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '1') {
				if (n - i >= h && m - j >= w && get(i, j, i + h, j + w) == h * w)
					lst = j + w;
				if (lst > j)
					gd[j] = i + h;
				if (gd[j] <= i)
					return 0;
			}
		}
	}
	return 1;
}

int mh, mw;
int mxh, mxw;
int mn[MX];
int mx[MX];

int run(int h) {
	int lb = mn[h];
	int rb = mx[h] + 1;
	while (rb - lb > 1) {
		int m1 = (lb + rb) / 2;
		if (check(h, m1))
			lb = m1;
		else
			rb = m1;
	}
	if (h * lb > mh * mw)
		mh = h, mw = lb;
	for (int i = h; i <= n; ++i)
		mx[i] = min(mx[i], lb);
	for (int i = 0; i <= h; ++i)
		mn[i] = max(mn[i], lb);
	return h * lb;
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
	mxh = n;
	mxw = m;
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
	for (int i = 0; i <= mxh; ++i)
		mn[i] = 0, mx[i] = mxw;
	mh = 0;
	mw = 0;
	int lb1 = 1;
	int rb1 = mxh;
	while (rb1 > lb1) {
		int m1 = lb1 + (rb1 - lb1) / 3;
		int m2 = m1 + max(1, (rb1 - lb1) / 3);
		if (run(m1) >= run(m2))
			rb1 = m2 - 1;
		else
			lb1 = m1 + 1;
	}
	run(lb1);
	cout << mh * mw << "\n";
	return 0;
}


