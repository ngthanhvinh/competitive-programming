#include <bits/stdc++.h>
#define ff(i, a, b) for(int i = (a), _b = (b); i <= _b; i++)
#define fb(i, a, b) for(int i = (a), _b = (b); i >= _b; i--)
#define pb push_back
#define fi first
#define se second

typedef long long ll;
using namespace std;
typedef vector <int> vi;
typedef pair <int, int> ii;

const ll N = 1000ll * 1000 * 1000 * 1000 * 1000, M = 1ll * 1000 * 1000;
ll cur = 1, val = 1;

ii f[100][M];
int s[M];

int ss(ll x) {
    int r = 0;
    while (x) { r += x % 10; x /= 10; }
    return r;
}

int main(void) {
	//ll z = 1; ff(i, 2, N) z += s(z); cout << z << endl;
	ff(j, 0, M - 1) s[j] = ss(j);
	ff(i, 0, 99) fb(j, M - 1, 0) {
		int y = j + s[j] + i;
		if (y >= M) f[i][j] = ii(y - M, 1);
		else { f[i][j] = f[i][y]; ++f[i][j].se; }
	}
	int gap = 10000000;
	for (ll rep = 0;; ++rep) {
		cerr << cur << endl;
		for (ll a = rep * gap, b = (rep + 1) * gap; a < b; ++a) {
			int SS = ss(a);
			ii nxt = f[SS][val];
			if (cur + nxt.se <= N) {
				cur += nxt.se;
				val = nxt.fi;
			}
			else while (cur < N) {
				++cur; val += s[val] + SS;
			}
			if (cur == N) return cout << a << " " << val << endl, 0;
		}
	}
	return 0;
}
