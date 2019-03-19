#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > ans;

bool cmp(vector<int> &a, vector<int> &b) { return a.size() < b.size(); }

int main() {
	freopen("out.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		int k; cin >> k; ++k;
		vector <int> cur;
		while(k--) {
			int x; cin >> x; cur.push_back(x);
		}
		cur.pop_back();
		sort(cur.begin(), cur.end());
		ans.push_back(cur);
	}
	sort(ans.begin(), ans.end(), cmp);
	for (int i = 0; i < ans.size(); ++i) {
		for (int j = 0; j < ans[i].size(); ++j) cerr << ans[i][j] << ' '; cerr << endl;
	}
}