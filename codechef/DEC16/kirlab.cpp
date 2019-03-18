#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;

const int N = 100010;
const int MAX = 10000010;

int n, a[N], f[N];
int d[MAX];

void sieve() {
	d[0] = d[1] = 1;
	for (int i = 2; i < MAX; ++i) if (!d[i]) {
		for (int j = i; j < MAX; j += i) d[j] = i;
	}
}

int mx[MAX];
vector <int> dvs;

void process(int cur) {
	dvs.clear();
	while(cur != 1) { int x = d[cur]; dvs.push_back(x); while(cur % x == 0) cur /= x; }
}

int get() {
	int ans = 0;
	for (int i = 0; i < dvs.size(); ++i) ans = max(ans, mx[dvs[i]]);
	return ans + 1;
}

void upd(int cur) {
	for (int i = 0; i < dvs.size(); ++i) mx[dvs[i]] = f[cur];
}

int main() {
	sieve();
	int t; scanf("%d", &t);
	while(t--) {
		scanf("%d", &n); for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		memset(f, 0, sizeof f);
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			process(a[i]);
			f[i] = get();
			upd(i);
			res = max(res, f[i]);
		}
		for (int i = 1; i <= n; ++i) process(a[i]), upd(0);
		printf("%d\n", res);
	}
}