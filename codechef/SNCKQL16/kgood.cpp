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

const int INF = 1e9, N = 100010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, k, cnt[26];
string s;

void solve() {
	cin >> s >> k; memset(cnt, 0, sizeof cnt);
	fo(i, 0, s.size()) cnt[s[i] - 'a']++;
	int ans = INF;
	fo(i, 0, 26) {
		// get min 
		if (!cnt[i]) continue;
		int mn = cnt[i], res = 0;
		//cout << i << ' ' << mn << endl;
		fo(j, 0, 26) if (cnt[j] != 0) {
			if (cnt[j] < mn) res += cnt[j];
			else if (cnt[j] > mn + k) res += cnt[j] - mn - k;
		}
		//cout << res << endl;
		ans = min(ans, res);
	}
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) solve();
}