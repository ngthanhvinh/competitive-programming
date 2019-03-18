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

const int INF = 1e9, N = 250251, mod = 250;
const ll BASE = 10000000000000000LL;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <long long> vi;
typedef vector <ii> vii;

long long f[2][mod];
int a[N];
int n;

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; i++) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}
#define Now 0
#define Next 1

int main() {
	ios_base::sync_with_stdio(false);
	n = 250250;
	ff(i, 1, n) a[i] = pw(i, i);
	f[Now][0] = 1LL;
	ff(i, 1, n) {
		fo(j, 0, mod) {
			f[Next][j] = (f[Next][j] + f[Now][j]) % BASE;
			f[Next][j] = (f[Next][j] + f[Now][(j - a[i] + mod) % mod]) % BASE;
		}
		fo(j, 0, mod) f[Now][j] = f[Next][j], f[Next][j] = 0LL;
	}
	printf("%016lld\n", (f[Now][0] - 1 + BASE) % BASE);
}