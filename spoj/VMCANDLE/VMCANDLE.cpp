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

ll n;

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	//cout << (ll)sqrt(1000000001000000000) << "\n";
	ll l = 0, r = 1e18 * 5;
	while(l != r) {
		ll mid = ((l + r) >> 1);
		if (mid - (ll)sqrt(mid) >= n) r = mid;
		else l = mid + 1; 
	}
	printf("%lld\n", l);
}