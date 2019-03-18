#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int n, dp[N], trace[N];
bool palind[N];

bool isPalind(int x) {
	stringstream ss; ss << x; 
	string s; ss >> s;

	for (int i = 0; i < s.size(); ++i) {
		if (s[i] != s[(int)s.size() - 1 - i]) {
			return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 1; i < N; ++i) {
		palind[i] = isPalind(i);
	}
	vector <int> vec;
	for (int i = 1; i < N; ++i) {
		if (palind[i]) {
			dp[i] = 1;
			trace[i] = i;
			vec.push_back(i);
			continue;
		}
		dp[i] = 1e9;
		for (int &j : vec) {
			if (dp[i] > dp[i - j] + 1) {
				dp[i] = dp[i - j] + 1;
				trace[i] = j;
			}
		}
	}

	int ntest; cin >> ntest;
	for (int itest = 1; itest <= ntest; ++itest) {
		int n; cin >> n;
		printf("Case #%d\n", itest);
		printf("%d ", dp[n]);

		vector <int> vres;
		while(n > 0) {
			vres.push_back(trace[n]);
			n -= trace[n];
		}
		sort(vres.begin(), vres.end(), greater<int>());
		for (int &i : vres) printf("%d ", i);
		printf("\n");
	}
}