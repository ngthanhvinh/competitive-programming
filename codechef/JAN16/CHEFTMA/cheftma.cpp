#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define init(x, n, y) x.assign(n, y);
#define fo(i, a, b) for (int i = a; i < b; ++i)
#define fod(i, a, b) for (int i = a; i >= b; --i)
using namespace std;
typedef pair <int,int> ii;
typedef vector <int> vi;
const int oo = 1e9+7;
const int N = 1e5+5;
 
int n, k, m;
vi tmp; int A[N], B[N];
multiset <int> S;
multiset <int> :: iterator it;
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int test; cin >> test;
	fo(Case, 1, test+1) {
		cin >> n >> k >> m; long long ans = 0;
		S.clear(); tmp.clear();
		fo(i, 1, n+1) cin >> A[i];
		fo(i, 1, n+1) cin >> B[i];

		fo(i, 1, n+1) if (A[i] > B[i]) tmp.pb(A[i]-B[i]);
		sort(tmp.begin(), tmp.end(), greater <int> ());
		
		fo(i, 0, k) { int V; cin >> V; S.insert(V); }
		fo(i, 0, m) { int V; cin >> V; S.insert(V); }
		fo(i, 0, tmp.size()) {
			it = S.upper_bound(tmp[i]); ans += tmp[i];
			if (it == S.begin()) continue ;
			--it; ans -= *it; S.erase(it);
		}
 
		cout << ans << "\n";
	}
}