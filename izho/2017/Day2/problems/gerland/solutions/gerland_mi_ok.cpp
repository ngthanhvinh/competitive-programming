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
const int MAXN = 120000;
const int MX = 1000010;

int n, m;
int h[MAXN];
int fv[MX];

void add(int x, int d) {
	for (; x < MX; x |= (x + 1))
		fv[x] += d;
}

int get(int x) {
	int ans = 0;
	for (; x >= 0; x = (x & (x + 1)) - 1)
		ans += fv[x];
	return ans;
}



int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf("%d", h + i);
	for (int i = 0; i < n - 1; ++i) {
		add(min(h[i], h[i + 1]), 1);
		add(max(h[i], h[i + 1]), -1);
	}
	for (int i = 0; i < m; ++i) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int p, v;
			scanf("%d%d", &p, &v);
			--p;
			if (p < n - 1) {
				add(min(h[p], h[p + 1]), -1);
				add(max(h[p], h[p + 1]), 1);
				add(min(v, h[p + 1]), 1);
				add(max(v, h[p + 1]), -1);
			}
			if (p > 0) {
				add(min(h[p], h[p - 1]), -1);
				add(max(h[p], h[p - 1]), 1);
				add(min(v, h[p - 1]), 1);
				add(max(v, h[p - 1]), -1);
			}
			h[p] = v;
		}
		else {
			int x;
			scanf("%d", &x);
			printf("%d\n", get(x));
		}
	}
	return 0;
}


