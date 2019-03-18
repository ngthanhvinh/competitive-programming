#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

const int N = 225;

int num = 0;
int len = 0;
int n;
int t[N];

vector <int> findSequence(int _n) {
	n = _n;
	for (int k = 0; k < 2; ++k) {
		for (int i = 1; i <= (n / 2) + 1; ++i) {
			vector <int> vec;
			for (int j = 1; j <= i; ++j) vec.push_back(k);
			if (!isSubsequence(vec)) {
				num = k;
				len = i - 1;
				break;
			}
		}
	}

	if (!len) {
		vector <int> vec;
		for (int i = 1; i <= n; ++i) vec.push_back(num ^ 1);
		return vec;
	}

	for (int i = 1; i <= len; ++i) {
		// find the number of {num ^ 1} before the i-th {num}
		bool flag0, flag1;
		int lef0 = i - 1;
		int rig0 = len - i;

		int l = 0, r = 0;

		vector <int> vec;
		for (int j = 1; j <= (n / 2) - rig0; ++j) {
			// num ^ 1 (j times), num, num (rig0 times) 
			vec.clear();
			for (int k = 1; k <= j; ++k) vec.push_back(num ^ 1);
			vec.push_back(num);
			for (int k = 1; k <= rig0; ++k) vec.push_back(num);
			flag0 = isSubsequence(vec);
			if (flag0) ++l;
			else break;
		}

		for (int j = 1; j <= (n / 2) - lef0; ++j) {
			// num (lef0 times), num, num ^ 1 (j times)
			vec.clear();
			for (int k = 1; k <= lef0; ++k) vec.push_back(num);
			vec.push_back(num);
			for (int k = 1; k <= j; ++k) vec.push_back(num ^ 1);
			flag1 = isSubsequence(vec);
			if (flag1) ++r;
			else break;
		}

		if (!flag1) t[i] = n - len - r;
		else t[i] = l; 
	}

	vector <int> res;
	for (int i = 1; i <= len; ++i) {
		int add = t[i] - t[i - 1];
		while(add--) res.push_back(num ^ 1);
		res.push_back(num);
	}

	int add = n - len - t[len];
	while(add--) res.push_back(num ^ 1);

	return res;
}