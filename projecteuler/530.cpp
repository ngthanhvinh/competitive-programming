#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 32000000;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

long long n = 10;
bitset <N> pr;
vector <long long> prime;
vector <long long> cnt;
long long ans = 1LL;

void sieve() {
	pr[0] = pr[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!pr[i]) { prime.pb(i); for (int j = i+i; j < N; j+=i) pr[j] = 1; }
	}
}

long long pw(long long a, int b) {
	long long res = 1LL;
	for (int i = 0; (1LL << i) <= b; ++i) {
		if (b & (1LL << i)) res *= a;
		a *= a;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	sieve();
	int m = prime.size();
	fo(i, 0, prime.size()) {
		if (prime[i] > n) break;
		long long p = prime[i];
		int Log = 0; long long cur = 1LL;
		while(cur <= n) cur *= p, Log++; Log--;
		cnt.assign(Log + 1, 0LL); cur = 1LL;
		for (int i = 1; i <= Log; ++i) {
			cur *= p; cnt[i] = n / cur;
		}
		ff(i, 1, Log) {
			long long r = 0LL; int t = (i>>1);
			if (i & 1) {
				r = 2LL * ((pw(p, t) - 1) / (p - 1));
				long long num = 0LL;
				ff(j, i, Log) {
					if (j & 1) num += cnt[j];
					else num -= cnt[j];
				}
			}
			else {
				r = 2LL * ((pw(p, t) - 1) / (p - 1)) + pw(p, t);
			}
		}
	}
}