#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
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
const int N = 1e4+5;
 
int n, a[N];
 
int main(void) {
	ios_base::sync_with_stdio(0);
	int test; cin >> test;
	fo(Case, 1, test+1) {
		cin >> n; int ans = oo;
		memset(a, 0, sizeof(a));
		fo(i, 1, n+1) cin >> a[i];
		fo(gcd, 2, 10001) {
			int cur = gcd, res = 0;
			fo(i, 1, n+1) {
				while (cur < a[i]) cur = cur + gcd;
				res += (cur-a[i]);
			}
 
			ans = min(ans, res);
		}
 
		cout << ans << "\n";
	}
}