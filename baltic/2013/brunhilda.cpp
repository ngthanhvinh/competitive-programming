#include <bits/stdc++.h>
using namespace std;

const int MAX = 10000000;
const int inf = 1e9 + 10;

int nprime, nquery;
int maxdiv[MAX + 5];
int dp[MAX + 5];

int main() {
	scanf("%d %d", &nprime, &nquery);
	for (int i = 1; i <= MAX; ++i) dp[i] = inf;
	for (int i = 1; i <= nprime; ++i) {
		int p; scanf("%d", &p);
		for (int j = 0; j <= MAX; j += p) maxdiv[j] = p;
	}
	
	int cur = 0;
	for (int i = 1; i <= MAX; ++i) {
		while(cur < i) {
			if (!maxdiv[cur] || cur + maxdiv[cur] <= i) ++cur;
			else break;
		}
		if (cur == i) continue;
		dp[i] = min(dp[i], dp[cur] + 1);
	}

	while(nquery--) {
		int n; scanf("%d", &n);
		if (dp[n] != inf) printf("%d\n", dp[n]);
		else printf("oo\n");
	}
}