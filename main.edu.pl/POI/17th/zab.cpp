#include <bits/stdc++.h>
using namespace std;

int n, k; long long m;
long long a[1000010];
int p[1000010], tmp[1000010];
int ans[1000010];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i], ans[i] = i;

	int l = 1, r = k + 1; p[1] = r;
	for (int i = 2; i <= n; ++i) {
		while(r < n && l < i && a[r + 1] - a[i] < a[i] - a[l]) {
			++r; ++l;
		}
		int x = 0;
		if (l == i) x = r; 
		else {
			if (a[r] - a[i] > a[i] - a[l]) x = r; else x = l;  
		}
		p[i] = x;
		//cerr << i << ' ' << p[i] << endl;
	}

	for (int j = 0; j <= 63; ++j) {
		if (m & (1LL << j)) {
			for (int i = 1; i <= n; ++i) ans[i] = p[ans[i]];
		}
		for (int i = 1; i <= n; ++i) tmp[i] = p[p[i]];
		for (int i = 1; i <= n; ++i) p[i] = tmp[i];
		//for (int i = 1; i <= n; ++i) cerr << p[i] << ' '; cerr << endl;
	}
	
	for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	printf("\n");
}