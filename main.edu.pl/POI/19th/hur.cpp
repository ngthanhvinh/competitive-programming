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

const int INF = 1e9, N = 250010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, a[N], b[N];
priority_queue < ii > q;
ll m;
vector <int> res;

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; ff(i, 1, n) cin >> a[i]; ff(i, 1, n) cin >> b[i];
	ff(i, 1, n) {
		m += a[i];
		if (m >= b[i]) q.push(ii(b[i], i)), m -= b[i];
		else {
			ii t = q.top(); int val = t.fi, pos = t.se;
			if (val > b[i]) {
				m += val, m -= b[i], q.pop(), q.push(ii(b[i], i));
			}
		}
	}
	while(!q.empty()) {
		res.pb(q.top().se); q.pop();
	}
	sort(res.begin(), res.end());
	cout << res.size() << endl;
	fo(i, 0, res.size()) cout << res[i] << ' '; cout << endl;
}