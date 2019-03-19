#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int n, m, cnt[N], s[N], l[N];
long long k;
int c;
int ans, num, a[N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) scanf("%d", l + i), k += l[i];
	if (k > n) return printf("0\n"), 0;
	for (int i = 1; i <= m; ++i) { scanf("%d", &c); s[c] = l[i]; }

	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		cnt[a[i]]++;
		if (s[a[i]]) {
			if (cnt[a[i]] == s[a[i]]) ++num; 
			else if (cnt[a[i]] == s[a[i]] + 1) --num;
		}
		if (i >= k) {
			cnt[a[i-k]]--;
			if (s[a[i-k]]) {
				if (cnt[a[i-k]] == s[a[i-k]]) ++num; 
				else if (cnt[a[i-k]] == s[a[i-k]] - 1) --num;
			}
		}
		else continue;
		if (num == m) ++ans;
	}

	printf("%d\n", ans);
}