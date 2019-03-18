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
const int N = 1005;
 
int n, m, L, R, U, D;
char a[N][N];
 
int GetMax(int a, int b, int c, int d) { return max(max(a, b), max(c, d)); }
 
int main(void) {
	ios_base::sync_with_stdio(0);
	int test; cin >> test;
	fo(Case, 1, test+1) {
		cin >> n >> m; int ans = oo;
		fo(i, 1, n+1) fo(j, 1, m+1) cin >> a[i][j];
		L = 0; R = 0; U = 0; D = 0;
		fo(i, 1, n+1) fo(j, 1, m+1) if (a[i][j] == '*') {
			if (!U) U = i;
			D = max(D, i);
		}
 
		fo(j, 1, m+1) fo(i, 1, n+1) if (a[i][j] == '*') {
			if (!L) L = j;
			R = max(R, j);
		}
 
		fo(i, U, D+1) fo(j, L, R+1) ans = min(ans, GetMax(i-U, D-i, j-L, R-j));
		if (!L && !U) cout << 0 << "\n";
		else cout << ans+1 << "\n";
	}
}