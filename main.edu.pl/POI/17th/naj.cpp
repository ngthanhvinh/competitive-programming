#include <bits/stdc++.h>
using namespace std;

const int N = 605;
const int MAX = 1e6 + 5;

int n, m;
long long x;
long long a[N];
int np[MAX];
int t[N * 70];
vector<int> pr;
map <long long, int> cnt;

void sieve() {
	np[0] = np[1] = 1;
	for (int i = 2; i < MAX; ++i) if (!np[i]) {
		for (int j = i+i; j < MAX; j += i) np[j] = 1;
		pr.push_back(i);
	}
}

int RAND(long long x) {
	int r = rand() % min(x - 1, 30000LL);
	r = max(r, 2);
	return r;
}

long long mul(long long p, long long q, long long md) { // p * q % md = ?
	long long res = 0;
	while(q) {
		if (q & 1) res = (res + p) % md;
		p = (p + p) % md;
		q >>= 1;
	}
	return res;
}

long long pw(long long a, long long p, long long md) { // a^p % md = ?
	long long res = 1;
	while(p) {
		if (p & 1) res = mul(res, a, md);
		a = mul(a, a, md);
		p >>= 1;
	}
	return res;
}

bool MillerRabin(long long x) {
	if (x % 2 == 0) return false;
	int NTEST = 50;
	int s = 0;
	long long d = x - 1;
	while(d % 2 == 0) ++s, d /= 2;

	while(NTEST--) {
		int r = RAND(x);
		long long b = pw(r, d, x);
		if (b == x - 1) return true;
		for (int k = 0; k <= s; ++k) {
			if (b == x - 1) return true;
			b = mul(b, b, x);
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	cin >> n;
	// case I: cubics
	for (int i = 1; i <= n; ++i) {
		cin >> x; long long X = x;
		for (int j = 0; j < pr.size(); ++j) {
			if (x % pr[j]) continue;
			while(x % pr[j] == 0) {
				x /= pr[j], cnt[pr[j]]++;
			}
		}
		if (x == 1) continue;
		int y = (int)sqrt(x);
		// case II: squares
		if (1LL * y * y == x) cnt[y] += 2;
		else {
			a[++m] = x;
		}
	}

	// case III: __gcd
	
	n = m;
	for (int i = 1; i < n; ++i) {
		for (int j = i+1; j <= n; ++j) {
			long long d = __gcd(a[i], a[j]);
			if (d > 1 && d < max(a[i], a[j])) {
				for (int k = 1; k <= n; ++k) {
					while(a[k] % d == 0) a[k] /= d, ++cnt[d];
				}
			}
		}
	}
	
	// case IV: Miller-Rabin primality test
	long long random = 1e18 + 3;
	vector < pair<long long,int> > cand;
	sort(a + 1, a + n + 1);
	int cur = 1;
	long long lst = 1;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 1) continue;
		if (a[i] > lst) {
			if (lst != 1) cand.push_back(make_pair(lst, cur));
			cur = 1; lst = a[i];
		} else ++cur;
	}
	if (lst != 1) cand.push_back(make_pair(lst, cur));

	for (auto &it : cand) {
		x = it.first;
		cur = it.second;
		if (MillerRabin(x)) cnt[++random] = cur;
		else cnt[++random] = cur, cnt[++random] = cur;
	}
	
	for (map<long long,int>::iterator iter = cnt.begin(); iter != cnt.end(); ++iter) {
		++t[iter->second];
	}
	for (int i = N * 70; i >= 0; --i) if (t[i]) {
		cout << i << '\n' << (1LL << t[i]) - 1 << endl;
		return 0;
	}
}