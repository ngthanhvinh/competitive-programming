#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, p;
int a[N], b[N];
int w[35], num[35];
vector<int> coeff[35];
int ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) cin >> b[i];
	sort(b + 1, b + m + 1);
	
	int cnt = 1;
	for (int i = 2; i <= m; ++i) {
		if (b[i] == b[i-1]) ++cnt;
		else w[++p] = b[i-1], num[p] = cnt, cnt = 1;
	}
	w[++p] = b[m]; num[p] = cnt;
	w[0] = 1;
	for (int i = p; i >= 1; --i) {
		w[i] = w[i] / w[i-1];
		for (int j = 1; j <= num[i]; ++j) coeff[i].push_back(1);
	}

	for (int i = 1; i < p; ++i) {
		for (int j = 1; j <= n; ++j) a[j] /= w[i];
		for (int j = 1; j <= n; ++j) {
			while(a[j] % w[i+1] != 0 && coeff[i].size()) {
				ans += coeff[i].back();
				--a[j];
				coeff[i].pop_back();
			}
		}

		vector<int> move;
		while(coeff[i].size()) {
			int cnt = w[i+1];
			int cur = 0;
			while(cnt-- > 0 && coeff[i].size()) {
				cur += coeff[i].back(); coeff[i].pop_back();
			}
			move.push_back(cur);
		}

		for (int j = (int)move.size() - 1; j >= 0; --j) {
			coeff[i+1].push_back(move[j]);
		}
	}	

	// TODO last one (w[p])
	for (int i = 1; i <= n; ++i) {
		a[i] /= w[p];
		while(a[i] > 0 && coeff[p].size()) {
			ans += coeff[p].back();
			--a[i];
			coeff[p].pop_back();
		}
	}

	printf("%d\n", ans);
}