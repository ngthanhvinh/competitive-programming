#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MAGIC = 335;
const int NBLOCK = N / MAGIC + 5;

int n, k;
int c[N], d[N], val[N];
vector <int> z[NBLOCK];
int lz[NBLOCK];

void upd_block(int block, int lim) {
	z[block].clear();
	for (int i = block * MAGIC; i < (block+1) * MAGIC && i <= lim; ++i) {
		val[i] += lz[block];
		z[block].push_back(val[i]);
	}
	lz[block] = 0;
	sort(z[block].begin(), z[block].end());
	// for (auto &v : z[block]) {
	// 	cerr << v << ' ';
	// }
	// cerr << endl;
}

void upd(int l, int r, int v, int lim) {
	int bl = l / MAGIC, br = r / MAGIC;
	if (bl == br) {
		for (int i = l; i <= r; ++i) val[i] += v;
		upd_block(bl, lim);
	}
	else {
		for (int i = l; i < (bl + 1) * MAGIC; ++i) val[i] += v;
		for (int block = bl + 1; block <= br - 1; ++block) lz[block] += v;
		for (int i = br * MAGIC; i <= r; ++i) val[i] += v;
		upd_block(bl, lim);
		upd_block(br, lim);
	}
}

int get() {
	int ret = 0;
	for (int block = 0; block <= (n - 1) / MAGIC; ++block) {
		int l = lower_bound(z[block].begin(), z[block].end(), -k - lz[block]) - z[block].begin();
		int r = upper_bound(z[block].begin(), z[block].end(), +k - lz[block]) - z[block].begin();
		ret += r - l;
	}
	return ret;
}

void solve() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i) cin >> c[i];
	for (int i = 0; i < n; ++i) cin >> d[i];

	for (int i = 0; i < n; ++i) val[i] = 0;
	for (int block = 0; block <= (n - 1) / MAGIC; ++block) {
		z[block].clear();
		lz[block] = 0;
	}

	vector <int> sc, sd;
	long long res = 0;

	for (int i = 0; i < n; ++i) {
		while(!sc.empty() && c[sc.back()] <= c[i]) {
			int l = 0, r = sc.back();
			if (sc.size() >= 2) l = sc[(int)sc.size()-2] + 1;
			upd(l, r, c[i] - c[sc.back()], i);
			sc.pop_back();
		}

		while(!sd.empty() && d[sd.back()] <= d[i]) {
			int l = 0, r = sd.back();
			if (sd.size() >= 2) l = sd[(int)sd.size()-2] + 1;
			upd(l, r, -d[i] + d[sd.back()], i);
			sd.pop_back();
		}

		sc.push_back(i);
		sd.push_back(i);
		upd(i, i, c[i] - d[i], i);

		res += get();
		//cerr << i << ' ' << res << endl;
	}

	cout << res << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		solve();
	}
}