#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int md = 1e9 + 7;
int n, m, k;
int ans;

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; ++i) {
		if (b & (1LL << i)) res = 1LL * res * a % md;
		a = 1LL * a * a % md;
	}
	return res;
}

struct data {
	int x; int y; int s;
	bool operator < (const data &a) { return x < a.x || (x == a.x && y < a.y); }
} a[N];
map <int,int> mp;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= k; ++i) {
		char c; cin >> c >> a[i].x >> a[i].y; a[i].s = (c == '+');
	}
	sort(a + 1, a + k + 1);

	// case 1
	int l = 1, r = 1, cntrow = 0;
	bool flag = true;
	while(l <= k) {
		while(r <= k && a[r].x == a[l].x) ++r; --r;
		++cntrow;
		for (int i = l + 1; i <= r; ++i) if (abs(a[i].y - a[l].y) % 2 != abs(a[i].s - a[l].s) % 2) flag = false;
		l = r + 1; r = l;
	}
	if (flag) ans = pw(2, n - cntrow);

	// case 2
	flag = true;
	for (int i = 1; i <= k; ++i) {
		int val = (a[i].x - 1 + a[i].s) % 2;
		if (mp.count(a[i].y) && mp[a[i].y] != val) flag = false;
		mp[a[i].y] = val;
	}
	if (!flag) {
		return cout << ans << endl, 0;
	}
	int add = pw(2, m - (int)mp.size());
	flag = true;
	if ((int)mp.size()) {
		map<int,int>::iterator it = mp.begin();
		int pos = it->first, val = it->second;
		for (it = mp.begin(); it != mp.end(); ++it) {
			if (abs(it->first - pos) % 2 != abs(it->second - val) % 2) flag = false;
		}
		if (flag) add--;
	} else add -= 2;

	ans += add; ans %= md; if (ans < 0) ans += md;
	cout << ans << endl;
}