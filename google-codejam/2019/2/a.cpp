#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
#define fi first
#define se second

const int N = 305;

int n, a[N], b[N];
bool smaller[N][N];
int cnt_smaller[N];
set < vector<int> > s;

void calc_perm() {
	vector <int> perm;
	for (int i = 1; i <= n; ++i) {
		cnt_smaller[i] = 0;
		perm.push_back(i);
		for (int j = 1; j <= n; ++j) if (j != i) {
			cnt_smaller[i] += smaller[i][j];
		}
		//cerr << i << ' ' << cnt_smaller[i] << endl;
	}
	sort(perm.begin(), perm.end(), [&](int x, int y) {
		return cnt_smaller[x] > cnt_smaller[y];
	});
	s.insert(perm);
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i];
	}

	vector < pair<ii, ii> > frac;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) if (i != j) {
			if (a[i] < a[j]) {
				smaller[i][j] = (b[i] <= b[j]);
				smaller[j][i] = (b[j] < b[i]);
				if (b[i] > b[j]) {
					frac.push_back({ {i, j}, {b[i] - b[j], a[j] - a[i]} });
				}
			} else if (a[i] == a[j]) {
				smaller[i][j] = (b[i] < b[j]);
				smaller[j][i] = (b[j] < b[i]);
			}
		}
	}

	sort(frac.begin(), frac.end(), [&](pair<ii,ii> &p, pair<ii,ii> &q) {
		return 1LL * p.se.fi * q.se.se < 1LL * p.se.se * q.se.fi;
	});

	s.clear();
	calc_perm();

	for (int i = 0; i < frac.size(); ) {
		pair<ii,ii> p = frac[i];
		//cerr << '\n';
		while(i < frac.size() && 1LL * p.se.fi * frac[i].se.se == 1LL * p.se.se * frac[i].se.fi) {
			pair<ii,ii> q = frac[i];
			//cerr << '(' << q.fi.fi << ' ' << q.fi.se << ')';
			//cerr << " (" << q.se.fi << ' ' << q.se.se << ')';
			//cerr << '\n';
			smaller[q.fi.fi][q.fi.se] ^= 1;
			smaller[q.fi.se][q.fi.fi] ^= 1;
			++i;
		}
		calc_perm();
	}

	cout << s.size() << endl;
}

int main() {
	ios_base::sync_with_stdio(false);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		solve();
	}
}