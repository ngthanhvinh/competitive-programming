#include <bits/stdc++.h>
using namespace std;

long long k, num;

void solve1() {
	cin >> k >> num;
	--num;
	long long x = num / (1LL << k), y = num % (1LL << k);
	long long layer = 0, nlayer = 1;
	long long curlen = (1LL << k);

	for (int i = k - 1; i >= 0; --i) {
		nlayer *= 2;
		if (x >> i & 1) { // the bottom half over the top half
			layer = nlayer - 1 - layer; x = curlen - 1 - x;
		}
		nlayer *= 2;
		if (y >> i & 1) { // the right half over the left half
			layer = nlayer - 1 - layer; y = curlen - 1 - y;
		}
		curlen >>= 1;
	}

	printf("%lld\n", layer + 1);
}

void solve2() {
	cin >> k >> num;
	--num;
	long long layer = num;
	long long curlen = 1;
	long long nlayer = (1LL << k) * (1LL << k);
	long long x = 0, y = 0;

	for (int i = k - 1; i >= 0; --i) {
		if (layer >> (2 * i + 1) & 1) {
			layer = nlayer - 1 - layer; y = 2 * curlen - 1 - y; 
		}
		nlayer >>= 1;
		if (layer >> (2 * i) & 1) {
			layer = nlayer - 1 - layer; x = 2 * curlen - 1 - x;
		}
		nlayer >>= 1;
		curlen *= 2;
	}

	printf("%lld\n", x * curlen + y + 1);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int q; // nquery
	cin >> q;
	while(q--) {
		int type; cin >> type;
		if (type == 1) solve1();
		else solve2();
	}
}