#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 1000010;

int n, h[N], m, k;
long long a[N];
vector<int> pre, suf;

void solve() {
	for (int i = 1; i <= n; ++i) a[i] = a[i-1] + h[i] - k;
	pre.clear(); pre.push_back(0); for (int i = 1; i <= n; ++i) if (a[i] < a[pre.back()]) pre.push_back(i);
	suf.clear(); suf.push_back(n); for (int i = n-1; i >= 0; --i) if (a[i] > a[suf.back()]) suf.push_back(i);
	int ptr = suf.size()-1;
	int ans = 0;
	for (int i = 0; i < pre.size(); ++i) {
		while(ptr >= 0 && a[suf[ptr]] >= a[pre[i]]) --ptr; ++ptr; 
		if (ptr < suf.size() && a[suf[ptr]] >= a[pre[i]]) ans = max(ans, suf[ptr] - pre[i]);
	}
	printf("%d ", ans);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", h + i);
	while(m--) {
		scanf("%d", &k);
		solve();
	}
	printf("\n");
}