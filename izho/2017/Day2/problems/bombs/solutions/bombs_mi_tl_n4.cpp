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
	for (int h = 1; h <= n; ++h)
		for (int w = 1; w <= m; ++w) {
			if (h * w <= mh * mw)
				continue;
			if (check(h, w))
				mh = h, mw = w;
		}
	cout << mh * mw << "\n";
	return 0;
}


