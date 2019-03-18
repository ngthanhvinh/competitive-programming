#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;

long long l[N];
long long r[N];

long long delivery(int n, int k, int L, int p[]) {
  for (int i = 1; i <= n; ++i) {
  	l[i] = (i >= k ? l[i - k] : 0) + p[i - 1] + min(L - p[i - 1], p[i - 1]);
  }
  for (int i = n; i >= 1; --i) {
  	r[i] = (i + k <= n ? r[i + k] : 0) + L - p[i - 1] + min(L - p[i - 1], p[i - 1]);
  }

  long long res = 9e18;
  for (int i = 0; i <= n; ++i) {
  	res = min(res, l[i] + r[i + 1]);
  }

  return res;
}
