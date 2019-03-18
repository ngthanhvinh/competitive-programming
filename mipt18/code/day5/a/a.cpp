#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e6 + 5;

int N;
int L[maxn], R[maxn];
int nx[maxn];

int _rand() {
	return rand() & ((1 << 16) - 1);
}

ll get_random() {
	ll ans = 0;
	for (int i = 0; i < 63; ++i) ans ^= (ll)(rand() & 1) << i;
	return ans;
}

struct BIT {
	ll T[maxn]; ll all;
	void reset() { memset(T, 0, sizeof T); all = 0; } 
	void add(int i, ll v) { all ^= v; for (++i;i < maxn; i += i & (-i)) T[i] ^= v; }
	ll get(int i) { ll ans = 0; for (++i; i; i-=i&(-i)) ans ^= T[i]; return ans; }
} T;

ll Mp[maxn];
map<ll, int> indx;

vector<int> ofL[maxn], ofR[maxn], ofU[maxn], ofD[maxn];
ll ans[maxn];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		L[i] = b, R[i] = d;
		Mp[i] = get_random(); indx[Mp[i]] = i;
		//cout << i << " = " << bitset<64>(Mp[i]).to_string() << endl;
		ofL[a].push_back(i); ofR[c].push_back(i);
		ofU[b].push_back(i); ofD[d].push_back(i);
	}
	ll all = 0;
	for (int i = 1; i < maxn; ++i) {
		for (auto u: ofR[i])
			T.add(R[u], Mp[u]), all ^= Mp[u];
		for (auto u: ofL[i])
			ans[u] ^= T.get(L[u]) ^ all;
	}
	T.reset();
	for (int i = 1; i < maxn; ++i) {
		for (auto u: ofR[i])
			T.add(L[u], Mp[u]);
		for (auto u: ofL[i])
			ans[u] ^= T.all ^ T.get(R[u] - 1);
	}
	T.reset(); all = 0;
	for (int i = maxn - 1; i >= 0; --i) {
		for (auto u: ofL[i]) 
			T.add(R[u], Mp[u]), all ^= Mp[u];
		for (auto u: ofR[i]) {
			ans[u] ^= T.get(L[u]) ^ all;
		}
	}
	T.reset(); all = 0;
	for (int i = maxn - 1; i >= 0; --i) {
		for (auto u: ofL[i]) 
			T.add(L[u], Mp[u]);
		for (auto u: ofR[i]) {
			ans[u] ^= T.get(R[u] - 1) ^ T.all;
		}
	}
	//for (int i = 1; i <= N; ++i)
	//	cout << i << " # " << bitset<64>(ans[i]).to_string() << endl;
	all = 0;
	for (int i = 0; i < maxn; ++i) {
		for (auto u: ofD[i]) all ^= Mp[u];
		for (auto u: ofU[i]) ans[u] ^= all;
	}
	all = 0;
	for (int i = maxn - 1; i >= 0; --i) {
		for (auto u: ofU[i]) all ^= Mp[u];
		for (auto u: ofD[i]) ans[u] ^= all;
	}
	for (int i = 1; i <= N; ++i) {
		ll f = all ^ Mp[i] ^ ans[i];
		//cout << i << " # " << bitset<64>(f).to_string() << endl;
		if (f == 0) continue;
		if (indx.count(f)) {
			nx[i] = indx[f];
		} else {
			nx[i] = -1;
		}
	}
	int ans = 0;
	for (int i = 1; i <= N; ++i) if (nx[i] > i && nx[nx[i]] == i) ++ans;
	cout << ans << endl;

}