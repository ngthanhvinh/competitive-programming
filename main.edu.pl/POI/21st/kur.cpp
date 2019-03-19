#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n, m;
int a[N];
int cnt[N][20];
vector<int> vec[N];

int get(int l, int r, int x) {
	int L = lower_bound(vec[x].begin(), vec[x].end(), l) - vec[x].begin();
	int R = upper_bound(vec[x].begin(), vec[x].end(), r) - vec[x].begin();
	return R - L;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i], vec[a[i]].push_back(i);
	for (int j = 0; j < 20; ++j) {
		for (int i = 1; i <= n; ++i) cnt[i][j] = cnt[i - 1][j] + (a[i] >> j & 1);
	}
	
	while(m--) {
		int l, r; cin >> l >> r;
		int x = 0;
		for (int j = 0; j < 20; ++j) {
			int b = 0;
			if (cnt[r][j] - cnt[l-1][j] > (r - l + 1) / 2) b = 1;
			x += (b << j);
		}
		if (get(l, r, x) > (r - l + 1) / 2) printf("%d\n", x); else printf("0\n");
	}
}