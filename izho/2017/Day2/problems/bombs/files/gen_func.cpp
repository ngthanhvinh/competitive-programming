#include "testlib.h"
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
const int MX = 2600;

char s[MX][MX];

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			s[i][j] = '0';
	int k = n / 2;
	for (int i = k; i < n; ++i)
		for (int j = 0; j < k - 1; ++j)
			s[i][j] = '1', s[j][i] = '1';
	vector<int> vv;
	for (int i = 0; i < k; ++i)
		vv.push_back(0), vv.push_back(1);
	shuffle(vv.begin(), vv.end());
	int now = k;
	int cnt = k - 1;
	for (int i = 0; i < vv.size(); ++i) {
		if (vv[i] == 0) {
			--now;
		}
		else {
			for (int j = k - 1; j > k - 1 - now; --j)
				s[cnt][j] = '1';
			--cnt;
		}
	}
	printf("%d %d\n", n, n);
	for (int i = 0; i < n; ++i)
		printf("%s\n", s[i]);
	return 0;
}


