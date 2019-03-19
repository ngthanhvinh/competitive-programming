#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int W = 100010;
const int P = 1000010;

int n, a[N], b[N], c[N];
int p, m[P], k[P], s[P];

int f[W];
vector <int> query;
int ans[P];

bool cmp(int x, int y) {
	int l,r;
	if (x < 0) l = a[-x]; else l = m[x];
	if (y < 0) r = a[-y]; else r = m[y];
	return l < r || (l == r && x < y);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; for (int i = 1; i <= n; ++i) cin >> c[i] >> a[i] >> b[i], query.push_back(-i);
	cin >> p; for (int i = 1; i <= p; ++i) cin >> m[i] >> k[i] >> s[i], s[i] += m[i], query.push_back(i);

	sort(query.begin(), query.end(), cmp);
	f[0] = 1e9 + 100;
	for (int i = 0; i < query.size(); ++i) {
		int x = query[i]; 
		if (x < 0) {
			x = -x;
			for (int i = W - 1; i >= 0; --i) {
				if (i - c[x] >= 0) f[i] = max(f[i], min(f[i - c[x]], b[x]));
			}
		}
		else {
			if (f[k[x]] > s[x]) ans[x] = 1;
		}
	}

	for (int i = 1; i <= p; ++i) printf((ans[i] == 1) ? "TAK\n" : "NIE\n");
}
