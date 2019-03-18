#include <bits/stdc++.h>
using namespace std;

const int N = 10005;
typedef pair<int,int> ii;

int n, m, d[N];
vector <ii> ed;
vector <int> p;

bool check(int k, bool flag = false) {
	int lim = 2 * (n - 1) - (n - k);
	int sum_deg = 0;
	for (int i = 0; i < k; ++i) {
		sum_deg += d[p[i]];
	}
	if (sum_deg > lim) return false;

	if (flag) {
		int rem = lim - sum_deg;
		for (int i = k; i < n; ++i) d[p[i]] = 1;
		if (rem > 0) {
			d[p[k]] += rem;
		}

		// build
		set <ii> s;
		for (int i = 0; i < n; ++i) s.insert(ii(d[i], i));
		while(!s.empty()) {
			assert(s.size() >= 2);
			auto p = (*s.begin());
			auto q = *(--s.end());
			s.erase(p);
			s.erase(q);

			assert(p.first == 1);
			ed.push_back({p.second, q.second});
			q.first--;
			if (q.first) {
				s.insert(q);
			}
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		++d[u];
		++d[v];
	} 
	
	for (int i = 0; i < n; ++i) p.push_back(i);
	sort(p.begin(), p.end(), [&](int x, int y) {
		return d[x] < d[y];
	});

	int low = 0, high = n;
	while(low < high) {
		int mid = ((low + high + 1) >> 1);
		if (check(mid)) low = mid;
		else high = mid - 1;
	}

	check(low, 1);
	printf("%d\n", n - low);
	printf("%d %d\n", n, n - 1);
	for (auto &e : ed) {
		printf("%d %d\n", e.first, e.second);
	}
}