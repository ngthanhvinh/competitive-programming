#include "Annalib.h"
#include <bits/stdc++.h>
using namespace std;

vector <int> mp2[4];
vector <int> mp1[3];
bool broken[155];

int getbit(long long X, int i) {
	if (i <= 62) return (X >> i & 1);
	else return 0;
}

void Anna(int N, long long X, int K, int P[]) {
	mp1[0] = {0, 0, 1}; // 0
	mp1[1] = {0, 1, 1}; // 1
	mp1[2] = {1, 0, 0}; // 1
	mp2[0] = {0, 1, 0}; // 00
	mp2[1] = {1, 0, 1}; // 01
	mp2[2] = {1, 1, 0}; // 10
	mp2[3] = {1, 1, 1}; // 11

	memset(broken, 0, sizeof broken);
  for (int i = 0; i < K; ++i) broken[P[i]] = 1;

  int cur = 0;
  for (int i = 0; i < N; i += 3) {
  	int cnt = broken[i] + broken[i + 1] + broken[i + 2];
  	if (cnt >= 2) {
  		Set(i, 0);
  		Set(i + 1, 0);
  		Set(i + 2, 0);
  	}
  	else if (cnt == 0) {
  		int x = getbit(X, cur) + getbit(X, cur + 1) * 2;
  		Set(i, mp2[x][0]);
  		Set(i + 1, mp2[x][1]);
  		Set(i + 2, mp2[x][2]);
  		cur += 2;
  	}
  	else { // cnt = 1
  		if (getbit(X, cur)) {
  			int x = 2; if (broken[i]) x = 1; 
  			Set(i, mp1[x][0]), Set(i + 1, mp1[x][1]), Set(i + 2, mp1[x][2]);
  			++cur;
  		} else {
  			if (!broken[i + 2]) {
  				Set(i, mp1[0][0]), Set(i + 1, mp1[0][1]), Set(i + 2, mp1[0][2]);
  				++cur;
  			} else { // 00 or 10
  				int x = getbit(X, cur + 1) * 2;
  				Set(i, mp2[x][0]), Set(i + 1, mp2[x][1]), Set(i + 2, mp2[x][2]);
  				cur += 2;
  			}
  		}
  	}
  }
}
