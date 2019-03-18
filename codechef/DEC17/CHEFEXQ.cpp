#include <bits/stdc++.h>
using namespace std;

const int N = 100005, MAGIC = 350;

int n, q, a[N];
vector<int> vec[MAGIC];
int fxor[MAGIC];

void prepare() {
	for (int i = 0; i <= (n-1) / MAGIC; ++i) {
		int l = i * MAGIC, r = min((i + 1) * MAGIC - 1, n - 1);
		fxor[i] = 0;
		for (int j = l; j <= r; ++j) {
			fxor[i] ^= a[j];
			vec[i].push_back(fxor[i]);
		}
		sort(vec[i].begin(), vec[i].end()); // sort all xor sums in a block for finding 
	}
}

void upd(int pos, int val) {
	a[pos] = val; // reset
	int block = pos / MAGIC;
	// reset all values in the current block
	vec[block].clear();
	fxor[block] = 0;
	for (int i = block * MAGIC; i <= min((block + 1) * MAGIC - 1, n - 1); ++i) {
		fxor[block] ^= a[i];
		vec[block].push_back(fxor[block]);
	}
	sort(vec[block].begin(), vec[block].end());
}

void query(int pos, int val) {
	int ans = 0;
	int block = pos / MAGIC;
	for (int i = 0; i < block; ++i) {
		int ptrL = lower_bound(vec[i].begin(), vec[i].end(), val) - vec[i].begin();
		int ptrR = upper_bound(vec[i].begin(), vec[i].end(), val) - vec[i].begin();
		ans += ptrR - ptrL; // count
		val ^= fxor[i];
	}
	int cur = 0;
	for (int i = block * MAGIC; i <= pos; ++i) {
		cur ^= a[i];
		if (cur == val) ++ans;
	}
	printf("%d\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for (int i = 0; i < n; ++i) cin >> a[i];
	prepare();

	while(q--) {
		int type, pos, val; cin >> type >> pos >> val; --pos;
		if (type == 1) {
			upd(pos, val);
		} else {
			query(pos, val);
		}
	}
}