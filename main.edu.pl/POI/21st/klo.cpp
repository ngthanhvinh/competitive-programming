#include <bits/stdc++.h>
using namespace std;

void out() { printf("0\n"); exit(0); }

set < pair<int,int> >::iterator it;
set < pair<int,int> > s;

const int N = 1000005;
int k, p, q, n;
int a[N];
int ptr;
int res[N];

bool check(int x, vector<int> &cand) {
	if (cand[x] == res[ptr]) return false;
	--a[cand[x]];
	int mx = 0;
	for (int val : cand) mx = max(mx, a[val]);
	++a[cand[x]];
	if (mx > n / 2) return false; return true;
}

int main() {
	scanf("%d%d%d", &k, &p, &q);
	for (int i = 1; i <= k; ++i) scanf("%d", &a[i]), n += a[i];
	if (n == 1) {
		if (p == q && a[p] > 0) {
			printf("%d\n", p);
			return 0;
		} else out();
	}
	--a[p]; --a[q]; n -= 2;
	if (a[p] < 0 || a[q] < 0) out();
	if (a[p] > (n + 1) / 2 || a[q] > (n + 1) / 2) out();

	for (int i = 1; i <= k; ++i) if (a[i]) s.insert(make_pair(a[i],i));
	res[++ptr] = p;

	while(!s.empty()) {
		// find candidates
		vector<int> cand;
		if (a[q]) cand.push_back(q);
		it = s.end(); --it;
		int t1 = it->second; s.erase(it); cand.push_back(t1);
		if (!s.empty()) {
			it = s.end(); --it; 
			int t2 = it->second; 
			cand.push_back(t2);
		}
		s.insert(make_pair(a[t1], t1));

		// find the number which will be deleted
		int del = 0;
		for (int i = 0; i < (int)cand.size(); ++i) if (check(i, cand)) {
			del = cand[i]; break;
		}			
		if (!del) out();

		it = s.find(make_pair(a[del], del));
		s.erase(it);
		--a[del]; res[++ptr] = del;
		--n;
		if (a[del] > 0) s.insert(make_pair(a[del], del));
	}
	res[++ptr] = q;
	for (int i = 2; i <= ptr; ++i) if (res[i] == res[i-1]) out();
	for (int i = 1; i <= ptr; ++i) printf("%d ", res[i]); printf("\n");
}
