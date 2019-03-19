#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;
const int md = 1e9 + 7;
const int BASE = 26;

int MAXLEN;
int n;
string s[N]; int sz[N];
int d[N];
int *h1[N], *h2[N], pw[N]; // for hashes
vector<int> vec[N];
long long ans;

int get1(int pos, int l, int r) {
	int ret = (h1[pos][r] - 1LL * h1[pos][l-1] * pw[r-l+1] % md) % md;
	if (ret < 0) ret += md;
	return ret;
}

int get2(int pos, int l, int r) {
	int ret = (h2[pos][l] - 1LL * h2[pos][r+1] * pw[r-l+1] % md) % md;
	if (ret < 0) ret += md;
	return ret;
}

bool check(int pos, int len) { // sz[pos] % len == 0
	return (get1(pos, 1, len)           == get2(pos, 1, len) 
			 && get1(pos, 1, sz[pos] - len) == get1(pos, len + 1, sz[pos]));
}

void prepare() {
	pw[0] = 1; for (int i = 1; i <= MAXLEN; ++i) pw[i] = 1LL * pw[i-1] * BASE % md;
	d[0] = d[1] = 1;
	for (int i = 2; i <= MAXLEN; ++i) if (!d[i]) {
		for (int j = i; j <= MAXLEN; j += i) d[j] = i;
	}
}

long long solve(int x) {
	long long ret = 0;
	sort(vec[x].begin(), vec[x].end());
	for (int i = 0; i < vec[x].size(); ) {
		auto val = vec[x][i];
		int cnt = 0;
		while(i < vec[x].size() && vec[x][i] == val) ++i, ++cnt;
		ret += 1LL * cnt * cnt;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> sz[i] >> s[i]; s[i] = ' ' + s[i];
		MAXLEN = max(MAXLEN, sz[i]);
		h1[i] = new int[sz[i] + 2];
		h2[i] = new int[sz[i] + 2]; 
		h1[i][0] = 0; for (int j = 1; j <= sz[i]; ++j) h1[i][j] = (1LL * h1[i][j-1] * BASE + s[i][j] - 'a') % md;
		h2[i][sz[i] + 1] = 0; for (int j = sz[i]; j >= 1; --j) h2[i][j] = (1LL * h2[i][j+1] * BASE + s[i][j] - 'a') % md;
 	}
	prepare();
	for (int i = 1; i <= n; ++i) {
		int tmp = sz[i];
		vector< pair<int,int> > pr;
		while(tmp != 1) {
			int x = d[tmp], cnt = 0;
			while(tmp % x == 0) tmp /= x, ++cnt;
			pr.push_back(make_pair(x, cnt));
		}
		vector<int> dvs; dvs.push_back(1);
		for (int j = 0; j < pr.size(); ++j) {
			int cur = pr[j].first, ex = pr[j].second;
			int SIZE = dvs.size();
			while(ex-- > 0) {
				for (int k = 0; k < SIZE; ++k) dvs.push_back(cur * dvs[k]);
				cur *= pr[j].first;
			}
		}

		for (int j : dvs) {
			if (check(i, j)) { vec[j].push_back(get1(i, 1, j)); break; }
		}
	}
	
	for (int i = MAXLEN; i >= 1; --i) if (vec[i].size()) {
		ans += solve(i);
	}

	cout << ans << '\n';
}