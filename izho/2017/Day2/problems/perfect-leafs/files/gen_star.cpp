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

vector<int> prm;
vector<pair<int, int> > eds;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int k = atoi(argv[1]);
	int l = atoi(argv[2]);
	int n = k * l + 1;
	printf("%d\n", n);
	for (int i = 0; i < n; ++i)
		prm.push_back(i);
	shuffle(prm.begin(), prm.end());
	int now = 1;
	for (int i = 0; i < k; ++i) {
		int lst = 0;
		for (int j = 0; j < l; ++j) {
			if (rnd.next(2))
				eds.push_back(make_pair(lst, now));
			else
				eds.push_back(make_pair(now, lst));
			lst = now++;
		}
	}
	shuffle(eds.begin(), eds.end());
	for (int i = 0; i < eds.size(); ++i)
		printf("%d %d\n", prm[eds[i].first] + 1, prm[eds[i].second] + 1);
	return 0;
}


