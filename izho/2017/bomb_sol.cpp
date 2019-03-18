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
const int MAXN = 2600;
 
int n, m;
char s[MAXN][MAXN];
int ans[MAXN];
int up[MAXN][MAXN];
int dw[MAXN][MAXN];
 
int main() {
 // freopen("bomb.in","r",stdin);
 // freopen("bomb.out","w",stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf(" %s", s[i]);
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
				++cnt, up[j][i] = cnt;
			if (s[j][i] == '1' && (j == n - 1 || s[j + 1][i] == '0')) {
				mxh = min(mxh, cnt);
				cnt = 0;
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		int cnt = 0;
		for (int j = n - 1; j >= 0; --j) {
			if (s[j][i] == '1')
				++cnt, dw[j][i] = cnt;
			else
				cnt = 0;
		}
	}
	for (int i = 0; i <= mxw; ++i)
		ans[i] = mxh;
 
	for (int i = 0; i < n; ++i) {
		int a = MAXN;
		int b = MAXN;
		int cnt = 0;
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '1') {
				a = min(a, up[i][j]);
				b = min(b, dw[i][j]);
				++cnt;
				ans[cnt] = min(ans[cnt], a + b - 1);
			}
			else {
				a = MAXN;
				b = MAXN;
				cnt = 0;
			}
		}
	}
 
	for (int i = 0; i < n; ++i) {
		int a = MAXN;
		int b = MAXN;
		int cnt = 0;
		for (int j = m - 1; j >= 0; --j) {
			if (s[i][j] == '1') {
				a = min(a, up[i][j]);
				b = min(b, dw[i][j]);
				++cnt;
				ans[cnt] = min(ans[cnt], a + b - 1);
			}
			else {
				a = MAXN;
				b = MAXN;
				cnt = 0;
			}
		}
	}
	int mh = 0;
	int mw = 0;
	for (int i = 1; i <= mxw; ++i)
		if (mh * mw < i * ans[i])
			mw = i, mh = ans[i];
	cout << mh * mw << "\n";
 
	return 0;
}