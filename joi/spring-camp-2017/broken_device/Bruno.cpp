#include "Brunolib.h"
#include <bits/stdc++.h>
using namespace std;

int val[8], bits[8];

long long Bruno(int N, int A[]) {
	val[1] = 0, bits[1] = 1;
	val[2] = 0, bits[2] = 2;
	val[3] = 1, bits[3] = 1;
	val[4] = 1, bits[4] = 1;
	val[5] = 1, bits[5] = 2;
	val[6] = 2, bits[6] = 2;
	val[7] = 3, bits[7] = 2;

	long long ret = 0;
	int cur = 0;
  for (int i = 0; i < N; i += 3) {
  	int x = 4 * A[i] + 2 * A[i + 1] + A[i + 2];
  	if (!x) continue;

  	if (cur > 61) break;
  	ret += 1LL * val[x] * (1LL << cur);
  	cur += bits[x];
  }
  return ret;
}
