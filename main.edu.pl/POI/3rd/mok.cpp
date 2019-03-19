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

const int INF = 0x3f3f3f3f, N = 4;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n;
vi a, SatisfiedRes;
queue <vi> q;
map <vi, int> cnt; 
int num;

void debug(vi v) {
	fo(i, 0, v.size()) cout << v[i] << ' '; cout << "\n";
}

void bfs() {
	q.push(a);
	while(!q.empty()) {
		num++; vi b = q.front(); q.pop();
		cout << "num: " << num << "\n";
		fo(i, 0, n) cout << b[i] << ' '; cout << "\n";
		fo(i, 0, n) {
			vi c = b; 
			if (c[i]) { c[i] = 0; if (!cnt[c]) { cout << "1 "; cnt[c] = cnt[b] + 1; q.push(c); debug(c); cout << cnt[c] << "\n"; } }
			fo(j, 0, n) {
				//cout << i << ' ' << j << "\n";
				if (i == j) continue;
				if (b[i] + b[j] <= a[j]) { cout << "2 "; c.clear(); c = b; c[i] = 0; c[j] = b[i] + b[j]; if (!cnt[c]) { cnt[c] = cnt[b] + 1; q.push(c); debug(c); cout << cnt[c] << "\n"; } }
				else if (b[i] + b[j] > a[j] && b[j] < a[j]) { cout << "3 "; c.clear(); c = b; c[i] = c[i] - a[j] + b[j]; b[j] = a[j]; if (!cnt[c]) { cnt[c] = cnt[b] + 1; q.push(c); debug(c); cout << cnt[c] << "\n"; } }
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	fo(i, 0, n) { int x; cin >> x; a.pb(x); }
	cnt[a] = 0;
	fo(i, 0, n) { int x; cin >> x; SatisfiedRes.pb(x); }
	if (a == SatisfiedRes) return cout << "0\n", 0;
	bfs();
	if (!cnt[SatisfiedRes]) return cout << "NIE\n", 0;
	cout << cnt[SatisfiedRes] << "\n";
}