#include <bits/stdc++.h>
#include "library.h"
using namespace std;

const int N =	1005;

int n;
int pos[N];
int res[N];
int cur;
int same[10];
vector <int> vec[10][2];

int query(vector<int> &v) {
	if (v.empty()) return 0;
	vector<int> M(n, 0);
	for (int &i : v) M[i - 1] = 1;
	return Query(M);
}

void ask() {
	for (int j = 0; j < 10; ++j) {
		vec[j][0].clear();
		vec[j][1].clear();
	}
	for (int i = 1; i <= n; ++i) {
		if (!pos[i]) {
			for (int j = 0; j < 10; ++j) {
				vec[j][i >> j & 1].push_back(i);
			}
		}
	}

	for (int j = 0; j < 10; ++j) {
		int t0 = query(vec[j][0]);
		int t1 = query(vec[j][1]);
		if (t0 == t1 + 1) {
			same[j] = 0;
		} else if (t1 == t0 + 1) {
			same[j] = 1;
		} else same[j] = -1;
	}

	int x = 0, y = 0;
	int dif = -1;
	for (int j = 0; j < 10; ++j) {
		if (same[j] != -1) {
			x ^= (same[j] << j);
			y ^= (same[j] << j);
		} else {
			if (dif == -1) {
				dif = j;
				y |= (1 << j); // x = 0, y = 1
				continue;
			}
			// ask one more time
			vector <int> v0, v1;
			for (int i = 1; i <= n; ++i) {
				if (!pos[i]) {
					if (i >> dif & 1) v0.push_back(i);
					else if ( (!(i >> dif & 1)) && (!(i >> j & 1)) ) v0.push_back(i);
					else v1.push_back(i);
				}
			}
			int t0 = query(v0);
			int t1 = query(v1);
			if (t0 > t1) { // x = 0, y = 1
				y |= (1 << j);
			} else { // x = 1, y = 0
				x |= (1 << j);
			}
		}
	}

	if (cur != 0) {
		vector<int> v; v.push_back(res[cur]); v.push_back(x);
		if (query(v) == 1) pos[x] = cur + 1, pos[y] = n - cur, res[cur + 1] = x, res[n - cur] = y;
		else pos[x] = n - cur, pos[y] = cur + 1, res[n - cur] = x, res[cur + 1] = y;
 	}
 	else {
 		res[1] = x; pos[x] = 1;
 		res[n] = y; pos[y] = n;
 	}
}

void Solve(int _n) {
	n = _n;
	for (int i = 1; i <= n / 2; ++i) {
		ask();
		++cur;
	}
	if (n & 1) {
		for (int i = 1; i <= n; ++i) if (!pos[i]) pos[i] = (n + 1) / 2, res[(n + 1) / 2] = i;
	}

	vector<int> reply(n, 0);
	for (int i = 1; i <= n; ++i) reply[i - 1] = res[i];
	Answer(reply);
}
