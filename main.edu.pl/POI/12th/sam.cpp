#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int P = 500010;

int n, k, p;
int a[P];
int lst[N], nxt[P];
int ans;

int main() {
	scanf("%d%d%d", &n, &k, &p);
	for (int i = 1; i <= p; ++i) scanf("%d", a + i);

	for (int val = 1; val <= n; ++val) lst[val] = p + 1;
	for (int i = p; i >= 1; --i) {
		nxt[i] = lst[a[i]];
		lst[a[i]] = i;
	}
	memset(lst, 0, sizeof lst);

	set < pair<int,int> > s;
	for (int i = 1; i <= p; ++i) {
		int cur = a[i];
		int add = 1;
		
		set < pair<int,int> >::iterator iter = s.find(make_pair(lst[cur], cur));
		if (iter != s.end()) s.erase(iter), add = 0;

		if (s.size() == k) {
			iter = s.end(); --iter;
			s.erase(iter);
		}
		
		s.insert(make_pair(nxt[i], cur));
		lst[cur] = nxt[i];
		ans += add;
	}

	printf("%d\n", ans);
}