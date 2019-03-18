#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, a[N], f[N];
vector <int> vec[N];
long long res;
int diff;
set <int> s;

// BIT
int T[N];
void upd(int x) { for (; x > 0; x -= x & -x) T[x]++; }
int get(int x) { int ret = 0; for (; x < N; x += x & -x) ret += T[x]; return ret; }

void dbg(set <int> &S) {
	cerr << "debug\n";
	for (auto &i : S) cerr << i << ' '; cerr << endl;
}

int main() {
	// freopen("sort.in", "r", stdin);
	// freopen("sort.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n;
	vector < pair<int,int> > order;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		order.push_back(make_pair(a[i], i));
	}
	sort(order.begin(), order.end());
	for (int i = 0; i < n; ++i) {
		a[order[i].second] = i + 1;
	}
	for (int i = 1; i <= n; ++i) cerr << a[i] << ' '; cerr << endl;

	for (int i = 1; i <= n; ++i) {
		f[i] = get(a[i] + 1);
		vec[f[i]].push_back(i);
		upd(a[i]);
	}

	res = n;
	for (int &i : vec[0]) s.insert(i);
	for (set<int>::iterator it = ++s.begin(); it != s.end(); ++it) {
		int cur = (*it) - (*prev(it));
		if (cur > 1) diff += cur;
	}
	dbg(s);

	for (int i = 1; i <= n; ++i) {
		assert(s.size() > 0);

		// move all positions to the right
		set<int>::iterator it = --s.end();
		int cur = max(n + 1, (*it) + 1);
		s.insert(cur);
		if (cur - (*it) > 1) diff += cur - (*it);
		
		it = s.begin();
		if (*next(it) - (*it) > 1) diff -= *next(it) - (*it);
		s.erase(s.begin());
		// no values being added

		for (int &pos : vec[i]) {
			s.insert(pos);
			it = s.find(pos);
			if (it != s.begin() && it != --s.end()) {
				diff -= (*next(it)) - (*prev(it)); // obviously > 1
			}
			if (it != s.begin()) {
				int cur = (*it) - (*prev(it));
				if (cur > 1) diff += cur;
			}
			if (it != --s.end()) {
				int cur = (*next(it)) - (*it);
				if (cur > 1) diff += cur;
			}
		}
		dbg(s);

		cerr << "diff " << diff << endl;
		res += diff;
	}

	printf("%lld\n", res);
}