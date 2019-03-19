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

const int INF = 0x3f3f3f3f, N = 30010;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n; 
int a[N], T[N];
int Original[N];

void upd(int x, int v) { for(; x < N; x += x & -x) T[x] += v; }
int get(int x) { int res = 0; for(; x > 0; x -= x & -x) res += T[x]; return res; } 

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	ff(i, 1, n) cin >> a[i];
	ff(i, 1, n) { a[i] = i - a[i]; upd(i, 1); }
	fod(i, n, 1) {
		int l = 1, r = n;
		if (get(n) < a[i] || get(1) > a[i]) return cout << "NIE\n", 0;
		while(l != r) {
			int mid = ((l + r) >> 1);
			if (get(mid) < a[i]) l = mid + 1;
			else r = mid;
		}
		//cout << l << "\n";
		Original[i] = l;
		upd(l, -1);
		//ff(i, 1, n) cout << get(i) << ' '; cout << "\n";
	}
	ff(i, 1, n) cout << Original[i] << "\n";
}