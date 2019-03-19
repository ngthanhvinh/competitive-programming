#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const long long inf = 9e18;

int n, x[N], y[N], t[N];
long long ans[2][2], coor[2][2];

long long calc(int c, vector < pair<int,int> > &vec) {
	long long ret = 0;
	for (int i = 0; i < vec.size(); ++i) {
		if (ret <= inf - 1LL * abs(c - vec[i].first) * vec[i].second)
			ret += 1LL * abs(c - vec[i].first) * vec[i].second;
		else return inf;
	}
	return ret;
}

void solve(int type) { // [%2=0, %2=1]
	vector < pair<int, int> > vec;
	if (type == 0) { // X
		for (int i = 1; i <= n; ++i) vec.push_back(make_pair(x[i], t[i]));
	} else { // Y
		for (int i = 1; i <= n; ++i) vec.push_back(make_pair(y[i], t[i]));
	}
	sort(vec.begin(), vec.end());

	long long L = 0, R = 0;
	for (auto &it : vec) R += it.second;
	vector<int> cand;
	cand.push_back(vec[0].first);
	for (int i = 0; i < vec.size(); ++i) {
		L += vec[i].second; R -= vec[i].second;
		if (R < L) {
			cand.push_back(vec[i].first);
			if (i > 0) cand.push_back(vec[i-1].first);
			break;
		}  
	}

	for (int c : cand) {
		for (int v = -1; v <= 1; ++v) {
			long long res = calc(c + v, vec);
			if (ans[type][(c + v) & 1] > res) 
				ans[type][(c + v) &1] = res, coor[type][(c + v) &1] = c + v;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int X, Y; cin >> X >> Y;
		x[i] = X - Y;
		y[i] = X + Y;
		cin >> t[i];
	}
	for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) ans[i][j] = inf;
	solve(0);
	solve(1);

	long long mn = inf, ansx = 0, ansy = 0;
	for (int i = 0; i < 2; ++i) {
		if (mn > ans[0][i] + ans[1][i]) {
			mn = ans[0][i] + ans[1][i];
			ansx = coor[0][i];
			ansy = coor[1][i];
		}
	}

	cout << (ansx + ansy) / 2 << ' ' << (ansy - ansx) / 2 << '\n';
}