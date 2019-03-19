#include <bits/stdc++.h>
using namespace std;

const int N = 50005;

int a, b, c;
int d[N];

void prep() {
	d[0] = d[1] = 1;
	for (int i = 2; i < N; ++i) if (!d[i]) {
		for (int j = i; j < N; j += i) d[j] = i;
	}
	for (int i = 2; i < N; ++i) {
		int prv = i / d[i];
		if (prv % d[i] != 0) d[i] = -d[prv]; else d[i] = 0;
	}
	for (int i = 1; i < N; ++i) d[i] = d[i - 1] + d[i];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	prep();

	int tt; cin >> tt;
	while(tt--) {
		cin >> a >> b >> c;
		a /= c; b /= c;
		if (a < b) swap(a, b);

		int pa = a, pb = b, pos = 1;
		long long ans = 0;
		while(pos <= b) {
			int nxt = b + 1;
			nxt = min(nxt, (a + pa - (a % pa != 0)) / pa);
			nxt = min(nxt, (b + pb - (b % pb != 0)) / pb);

			ans += 1LL * pa * pb * (d[nxt-1] - d[pos-1]);
			pa = a / nxt;
			pb = b / nxt;
			pos = nxt;
		}

		printf("%lld\n", ans);
	}
}