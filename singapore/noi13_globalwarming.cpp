#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n;
vector< pair<int,int> > vec;
int ans, cur;
bool check[N];

void add(int pos) {
	check[pos] = 1;
	if (pos > 1 && pos < n && check[pos - 1] && check[pos + 1]) {
		--cur; return;
	}
	bool flag = false;
	flag |= (pos > 1 && check[pos - 1]);
	flag |= (pos < n && check[pos + 1]);
	if (!flag) ++cur;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x; 
		vec.push_back(make_pair(x, i));
	}
	sort(vec.begin(), vec.end(), greater< pair<int,int> >());
	
	for (int i = 0; i < vec.size(); ) {
		int height = vec[i].first;
		while(i < vec.size() && vec[i].first == height) {
			add(vec[i].second);
			++i;
		}
		ans = max(ans, cur);
	}

	cout << ans << endl;
}