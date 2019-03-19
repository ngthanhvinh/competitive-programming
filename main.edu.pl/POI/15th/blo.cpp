#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n, k, a[N], p[N]; 
long long f[N];
long long T[N << 2];
int cnt[N << 2];
vector <int> Z;

#define mid ((l + r) >> 1)

void upd(int v, int l, int r, int pos, int x) {
	if (l > r || l > pos || r < pos) return;
	if (l == r) { T[v] += x * Z[pos - 1]; cnt[v] += x; return; }
	upd(v << 1, l, mid, pos, x); upd(v << 1 | 1, mid + 1, r, pos, x);
	T[v] = T[v << 1] + T[v << 1 | 1];
	cnt[v] = cnt[v << 1] + cnt[v << 1 | 1];
}

int _cnt;
long long _T;
int median(int v, int l, int r, int lim) {
	if (l == r) {
		_cnt += cnt[v]; _T += T[v];
		return l;
	}
	if (cnt[v << 1] >= lim) return median(v << 1, l, mid, lim);
	else {
		_cnt += cnt[v << 1], _T += T[v << 1];
		return median(v << 1 | 1, mid + 1, r, lim - cnt[v << 1]);
	}
}

int cur_i, cur_median;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i], f[i] = f[i - 1] + a[i], Z.push_back(a[i]);
	sort(Z.begin(), Z.end());
	for (int i = 1; i <= n; ++i) {
		p[i] = lower_bound(Z.begin(), Z.end(), a[i]) - Z.begin() + 1;
	}

	long long ans = 1e18;
	for (int i = 1; i <= n; ++i) {
		if (i <= k) {
			upd(1, 1, N - 1, p[i], 1);
			if (i < k) continue;
		}
		else {
			upd(1, 1, N - 1, p[i - k], -1);
			upd(1, 1, N - 1, p[i], 1);
		}
		_cnt = 0; _T = 0;
		int x = median(1, 1, N - 1, (k + k % 2) / 2);
		x = Z[x - 1];
		long long res = 1LL * _cnt * x - _T + f[i] - f[i - k] - _T - 1LL * (k - _cnt) * x;
		
		if (ans > res) {
			ans = res;
			cur_i = i;
			cur_median = x;
		}
	}

	cout << ans << endl;
	for (int i = 1; i < cur_i - k + 1; ++i) cout << a[i] << endl;
	for (int i = cur_i - k + 1; i <= cur_i; ++i) cout << cur_median << endl;
	for (int i = cur_i + 1; i <= n; ++i) cout << a[i] << endl;
}