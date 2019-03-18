#include <bits/stdc++.h>
using namespace std;

const int N = 400005, MAGIC = 525;
const int Q = 25005;

int n, q;
int a[N];
priority_queue <int> pq[N / MAGIC + 5];
priority_queue < int, vector<int>, greater<int> > changes[N / MAGIC + 5];

void restore(int block) { // restore a[]
	for (int i = block * MAGIC; i < n && i < (block + 1) * MAGIC; ++i) {
		changes[block].push(a[i]);
		a[i] = changes[block].top();
		changes[block].pop();
	}

	changes[block] = priority_queue < int, vector<int>, greater<int> >();
}

void remake(int block) { // make a new pq
	pq[block] = priority_queue<int>();
	for (int i = block * MAGIC; i < n && i < (block + 1) * MAGIC; ++i) {
		pq[block].push(a[i]);
	}
}

void solve(int s, int t, int &val) {
	int bs = s / MAGIC, bt = t / MAGIC;
	if (bs == bt) {
		restore(bs);
		for (int i = s; i <= t; ++i) if (val < a[i]) swap(val, a[i]);
		remake(bs);
	} else {
		restore(bs); restore(bt);

		for (int i = s; i < (bs + 1) * MAGIC; ++i) 
			if (val < a[i]) swap(val, a[i]);
		for (int i = bs + 1; i < bt; ++i) {
			pq[i].push(val);
			changes[i].push(val);
			val = pq[i].top(); pq[i].pop();
		}
		for (int i = bt * MAGIC; i <= t; ++i) 
			if (val < a[i]) swap(val, a[i]);

		remake(bs); remake(bt);
	}
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

	for (int i = 0; i < n; ++i) pq[i / MAGIC].push(a[i]);

	while(q--) {
		int s, t, p; scanf("%d%d%d", &s, &t, &p);
		--s; --t;
		if (s <= t) { // [s...t]
			solve(s, t, p);
		} else { // [s...n-1], [0...t]
			solve(s, n - 1, p);
			solve(0, t, p);
		}
		printf("%d\n", p);
	}
}