#include <bits/stdc++.h>
#include "messy.h"
using namespace std;

const int N = 128;
int n;
int p[N];

void add(int l, int r) {
	if (l == r) return;
	int mid = ((l + r) >> 1);
	// l...mid: 0
	// mid + 1...r: 1
	for (int i = l; i <= mid; ++i) {
		string s(n, '0');
		for (int j = l; j <= r; ++j) s[j] = '1';
		s[i] = '0';
		add_element(s);
	}

	add(l, mid);
	add(mid + 1, r);
}

void check(int l, int r, vector<int> &can) {
	if (l == r) {
		assert(can.size() == 1);
		p[l] = can[0];
		return;
	}

	vector <bool> have(n, 0);
	for (int i : can) have[i] = true;

	vector <int> can_lef, can_rig;
	for (int i : can) {
		string s(n, '1');
		for (int j = 0; j < n; ++j) if (!have[j]) s[j] = '0';
		s[i] = '0';
		
		if (check_element(s)) {
			can_lef.push_back(i);
		} else {
			can_rig.push_back(i);
		}
	}

	int mid = ((l + r) >> 1);
	check(l, mid, can_lef);
	check(mid + 1, r, can_rig);
}

vector<int> restore_permutation(int _n, int w, int r) {
    n = _n;
    add(0, n - 1);
    compile_set();

    vector <int> can;
    for (int i = 0; i < n; ++i) can.push_back(i);
    check(0, n - 1, can);

	vector <int> P(n);
	for (int i = 0; i < n; ++i) P[p[i]] = i;
    return P;
}
