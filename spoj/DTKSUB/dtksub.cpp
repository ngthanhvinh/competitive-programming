#include <bits/stdc++.h>
using namespace std;
const int N = 50010;
#define fi first
#define se second
typedef pair <int, int> ii;
typedef pair <ii, int> II;

int n, k, cnt, suf[N][17], sa[N], lcp[N];
string s;

void build() {
	ii a[N]; cnt = 0; for (int i = 1; i <= n; i++) a[i] = ii(s[i], i);
	sort(a + 1, a + n + 1); for (int i = 1; i <= n; i++) suf[a[i].se][0] = (a[i].fi == a[i-1].fi) ? cnt : ++cnt;
	II A[N];
	for (int i = 0; i < 16; i++) {
		for (int j = 1; j <= n; j++) A[j] = (j + (1<<i) <= n) ? II(ii(suf[j][i], suf[j + (1<<i)][i]), j) : II(ii(suf[j][i], 0), j);
		sort(A + 1, A + n + 1); cnt = 0;
		for (int j = 1; j <= n; j++) suf[A[j].se][i+1] = (A[j].fi == A[j-1].fi) ? cnt : ++cnt;
	}
}	

int find_lcp(int x, int y) {
	int len = 0;
	for (int i = 16; i >= 0; i--) 
		if (x + (1 << i) <= n+1 && y + (1 << i) <= n+1 && suf[x][i] == suf[y][i]) x += (1 << i), y += (1 << i), len += (1 << i);
	return len;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k >> s; 
	if (k == 1) return cout << n << endl, 0;
	s = '~' + s; build();
	for (int i = 1; i <= n; i++) sa[suf[i][16]] = i;
	for (int i = 1; i < n; i++) lcp[i] = find_lcp(sa[i], sa[i+1]);
	int mx = 0; deque <int> q; k--;
	for (int i = 1; i <= k-1; i++) {
		while(!q.empty() && q.back() > lcp[i]) q.pop_back();
		q.push_back(lcp[i]);
	}
	for (int i = k; i < n; i++) {
		while(!q.empty() && q.back() > lcp[i]) q.pop_back();
		if (!q.empty() && q.front() == lcp[i-k]) q.pop_front();
		q.push_back(lcp[i]);
		mx = max(mx, q.front());
	}
	cout << mx << endl;
}