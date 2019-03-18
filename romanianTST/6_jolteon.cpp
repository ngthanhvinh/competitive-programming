#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MAX = 1000005;
const int MAGIC = 250;

int n;
int a[N], prv[N];
long long mp[MAX];
int lst[MAX];

long long f[N], lz[N / MAGIC + 10];
vector<long long> vec[N / MAGIC + 10];
long long ans;

long long myrand() {	
	int rd1 = rand() % 50000 + 1;
	int rd2 = rand() % 40000 + 1;
	int rd3 = rand() % 60000 + 1;
	return 1LL * rd1 * rd2 * rd3;
}

void reset(int block) {
	lz[block] = 0;
	vec[block].clear();
	for (int i = block * MAGIC; i < min(n, (block + 1) * MAGIC); ++i) {
		vec[block].push_back(f[i]);
	}
	sort(vec[block].begin(), vec[block].end());
}

void upd(int pos, long long val) { // [0...pos]
	if (pos < 0) return; // -1

	int block = pos / MAGIC;

	for (int i = 0; i < block; ++i) lz[i] ^= val;

	for (int i = block * MAGIC; i < min(n, (block + 1) * MAGIC); ++i) {
		f[i] ^= lz[block];
		if (i <= pos) f[i] ^= val;
	}
	reset(block);
}

void get(int pos) { 
	// count the number of segments [i...pos] (i <= pos) that is valid

	int block = pos / MAGIC;
	for (int i = 0; i < block; ++i) 
		ans += upper_bound(vec[i].begin(), vec[i].end(), lz[i]) - lower_bound(vec[i].begin(), vec[i].end(), lz[i]);
	for (int i = block * MAGIC; i <= pos; ++i) ans += f[i] == 0;
}

int main() {
	srand(time(NULL));
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

	for (int i = 0; i < n; ++i) {
		if (!mp[a[i]]) mp[a[i]] = myrand(), lst[a[i]] = -1;
		prv[i] = lst[a[i]];
		lst[a[i]] = i;
	}

	for (int i = 0; i < n; ++i) {
		upd(prv[i], mp[a[i]]); // [0 ... prv[i]]
		get(i);
		// update pos
		if (i % MAGIC == MAGIC - 1) {
			reset(i / MAGIC);
		}
	}

	printf("%lld\n", ans);
}