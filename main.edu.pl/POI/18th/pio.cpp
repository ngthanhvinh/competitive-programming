#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n, a[N], p[N];
int L[N];
double sqt[N];

int findL(int p, int q) {
	int l = max(p, q), r = n;
	while(l < r) {
		int mid = ((l + r + 1) >> 1);
		if (a[p] + sqt[mid - p] < a[q] + sqt[mid - q]) r = mid - 1;
		else l = mid;
	}
	return l + 1;
}

void solve(bool flag) {
	deque <int> dq;
	int prv = -1e9;
	for (int i = 1; i <= n; ++i) {
		while(dq.size() > 1 && L[dq[1]] <= i) dq.pop_front();
		if (prv < a[i]) {
			prv = a[i];

			while(!dq.empty() && findL(dq.back(), i) <= L[dq.back()]) {
				dq.pop_back();
			}
			
			if (!dq.empty()) L[i] = findL(dq.back(), i);
			else L[i] = i;
			dq.push_back(i);
		}

		int cur = a[dq.front()] + (int)ceil(sqt[i - dq.front()]);
		if (!flag) p[i] = max(p[i], cur);
		else p[n + 1 - i] = max(p[n + 1 - i], cur);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 0; i < N; ++i) sqt[i] = sqrt(i);

	solve(0);
	for (int i = 1; i <= n / 2; ++i) swap(a[i], a[n + 1 - i]);
	solve(1);	
	for (int i = 1; i <= n / 2; ++i) swap(a[i], a[n + 1 - i]);

	for (int i = 1; i <= n; ++i) {
		printf("%d\n", max(0, p[i] - a[i]));
	}
}