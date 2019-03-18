#include <bits/stdc++.h>
using namespace std;

int D, p[33];
string s;

void solve() {
	cin >> D >> s;
	int n = s.size();
	s = ' ' + s;

	p[0] = 1;
	long long res = 0;
	for (int i = 1; i <= n; ++i) {
		p[i] = p[i - 1];
		if (s[i] == 'C') p[i] *= 2;
		else res += p[i];
	}

	int nchange = 0;
	while(res > D) {
		bool found = false;
		for (int i = n; i >= 2; --i) {
			if (s[i] == 'S' && s[i - 1] == 'C') {
				res -= p[i];
				res += (p[i] >> 1);
				p[i - 1] = (p[i] >> 1);
				++nchange;
				found = true;
				swap(s[i], s[i - 1]);
				break;
			}
		}
		if (!found) break;
	}

	if (res > D) printf("IMPOSSIBLE\n");
	else printf("%d\n", nchange);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve(); 
	}
}