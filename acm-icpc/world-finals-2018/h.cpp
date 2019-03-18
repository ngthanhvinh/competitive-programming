#include <bits/stdc++.h>
using namespace std;

#define double long double

const double EPS = 0.1;
const int N = 2000005;
const long long mod = 1e18 + 123;

int n, w, h;
bool check[N];
long long pw2[N];
map <long long, pair<double,double> > mp[4];

struct Query {
	double coor;
	int w; // +1 or -1
	int id; // 2 * i - 1 or 2 * i
	bool operator < (const Query &other) const {
		return coor < other.coor || (coor == other.coor && w < other.w);
	}
};
vector <Query> vec[4];

int which_part(int x, int y) {
	if (x == 0) return 0;
	else if (x == w) return 2;
	else if (y == 0) return 3;
	else return 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> w >> h;
	for (int i = 1; i <= n; ++i) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		int p = which_part(x1, y1);
		int q = which_part(x2, y2);
		if (p > q) swap(p, q), swap(x1, x2), swap(y1, y2);

		if (p == 0 && q == 1) {
			vec[0].push_back({y1 + EPS, +1, 2 * i - 1}); vec[0].push_back({h - EPS, 0, 2 * i - 1}); vec[0].push_back({h, -1, 2 * i - 1});
			vec[1].push_back({0 + EPS, +1, 2 * i - 1}); vec[1].push_back({x2 - EPS, 0, 2 * i - 1}); vec[1].push_back({x2, -1, 2 * i - 1}); 
			vec[1].push_back({x2 + EPS, +1, 2 * i}); vec[0].push_back({y1 - EPS, 0, 2 * i}); vec[0].push_back({y1, -1, 2 * i});
		}
		if (p == 1 && q == 2) {
			vec[1].push_back({0 + EPS, +1, 2 * i}); vec[1].push_back({x1 - EPS, 0, 2 * i}); vec[1].push_back({x1, -1, 2 * i});
			vec[1].push_back({x1 + EPS, +1, 2 * i - 1}); vec[2].push_back({y2 + EPS, 0, 2 * i - 1}); vec[2].push_back({y2, -1, 2 * i - 1});
			vec[2].push_back({y2 - EPS, +1, 2 * i}); vec[0].push_back({h - EPS, 0, 2 * i}); vec[0].push_back({h, -1, 2 * i});
		}
		if (p == 2 && q == 3) {
			vec[1].push_back({0 + EPS, +1, 2 * i}); vec[2].push_back({y1 + EPS, 0, 2 * i}); vec[2].push_back({y1, -1, 2 * i});
			vec[2].push_back({y1 - EPS, +1, 2 * i - 1}); vec[3].push_back({x2 + EPS, 0, 2 * i - 1}); vec[3].push_back({x2, -1, 2 * i - 1});
			vec[3].push_back({x2 - EPS, +1, 2 * i}); vec[0].push_back({h - EPS, 0, 2 * i}); vec[0].push_back({h, -1, 2 * i});
		}
		if (p == 0 && q == 3) {
			vec[1].push_back({0 + EPS, +1, 2 * i}); vec[3].push_back({x2 + EPS, 0, 2 * i}); vec[3].push_back({x2, -1, 2 * i});
			vec[3].push_back({x2 - EPS, +1, 2 * i - 1}); vec[0].push_back({y1 - EPS, 0, 2 * i - 1}); vec[0].push_back({y1, -1, 2 * i - 1});
			vec[0].push_back({y1 + EPS, +1, 2 * i}); vec[0].push_back({h - EPS, 0, 2 * i}); vec[0].push_back({h, -1, 2 * i});
		}
		if (p == 0 && q == 2) {
			vec[1].push_back({0 + EPS, +1, 2 * i - 1}); vec[2].push_back({y2 + EPS, 0, 2 * i - 1}); vec[2].push_back({y2, -1, 2 * i - 1});
			vec[2].push_back({y2 - EPS, +1, 2 * i}); vec[0].push_back({y1 - EPS, 0, 2 * i}); vec[0].push_back({y1, -1, 2 * i});
			vec[0].push_back({y1 + EPS, +1, 2 * i - 1}); vec[0].push_back({h - EPS, 0, 2 * i - 1}); vec[0].push_back({h, -1, 2 * i - 1});
		}
		if (p == 1 && q == 3) {
			vec[1].push_back({0 + EPS, +1, 2 * i - 1}); vec[1].push_back({x1 - EPS, 0, 2 * i - 1}); vec[1].push_back({x1, -1, 2 * i - 1});
			vec[1].push_back({x1 + EPS, +1, 2 * i}); vec[3].push_back({x2 + EPS, 0, 2 * i}); vec[3].push_back({x2, -1, 2 * i});
			vec[3].push_back({x2 - EPS, +1, 2 * i - 1}); vec[0].push_back({h - EPS, 0, 2 * i - 1}); vec[0].push_back({h, -1, 2 * i - 1});
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (i % 2 == 0) vec[i].push_back({0 + EPS, 0, 0}), vec[i].push_back({h - EPS, 0, 0});
		else vec[i].push_back({0 + EPS, 0, 0}), vec[i].push_back({w - EPS, 0, 0});
	}

	for (int id = 0; id < 4; ++id) {
		if (id == 0 || id == 1) sort(vec[id].begin(), vec[id].end());
		else sort(vec[id].begin(), vec[id].end()), reverse(vec[id].begin(), vec[id].end());
	}

	// 1 -> 2 -> 3 -> 0
	pw2[0] = 1;
	for (int i = 1; i < N; ++i) pw2[i] = 2LL * pw2[i - 1] % mod;

	pair <double, double> fi = {-1,-1}, se = {-1,-1};

	long long curhash = 0;
	int cnt = 0;

	for (int i = 1; ; i = (i + 1) % 4) {
		for (int k = 0; k < vec[i].size(); ) {
			double x = vec[i][k].coor;
			while(k < vec[i].size() && vec[i][k].coor == x) {
				auto j = vec[i][k];
				if (j.w == +1) {
					++cnt, curhash = (curhash + pw2[(j.id + 1) / 2] * (j.id & 1)) % mod;
					if (check[(j.id + 1) / 2]) assert(0);
					check[(j.id + 1) / 2] = 1;
				}
				if (j.w == -1) {
					--cnt, curhash = (curhash - pw2[(j.id + 1) / 2] * (j.id & 1) + mod) % mod;
					if (!check[(j.id + 1) / 2]) assert(0);
					check[(j.id + 1) / 2] = 0;
				}
				++k;
			}
			if (cnt == n) {
				// do something
				if (i == 1) fi = {x, h};
				if (i == 2) fi = {w, x};
				if (i == 3) fi = {x, 0};
				if (i == 0) fi = {0, x};
				if (mp[i].find(curhash) == mp[i].end()) mp[i][curhash] = fi;
				fi = {-1, -1};
			}
		}

		if (i == 0) break;
	}

	long long total = 0;
	total = (pw2[n + 1] - 2 + mod) % mod;
	for (int i = 0; i < 4; ++i) {
		for (auto &I : mp[i]) {
			long long J = (total - I.first + mod) % mod;
			for (int j = i + 1; j < 4; ++j) {
				if (mp[j].find(J) != mp[j].end()) {
					fi = I.second;
					se = mp[j][J];
					cout << 1 << '\n';
					cout << setprecision(6) << fixed << fi.first << ' ' << fi.second << ' ' << se.first << ' ' << se.second << endl;
					exit(0);
				}
			}
		}
	}

	// 2 points
	cout << 2 << '\n';
	cout << setprecision(6) << fixed << 0 + EPS << ' ' << h << ' ' << w - EPS << ' ' << 0 << '\n';
	cout << setprecision(6) << fixed << w << ' ' << h - EPS << ' ' << 0 << ' ' << 0 + EPS << '\n';
}