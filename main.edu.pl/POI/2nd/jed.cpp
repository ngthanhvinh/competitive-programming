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

const int INF = 0x3f3f3f3f, N = 100010, BASE = 10000;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n;
int Mod[101]; bool dp[101][20001];

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t; while(t--) {
		cin >> n;
		int cnt1 = 0, cnt2 = 0;
		while(n % 2 == 0) n /= 2, cnt1++;
		while(n % 5 == 0) n /= 5, cnt2++;
		
		ff(i, 1, cnt1) n *= 2;
		ff(j, 1, cnt2) n *= 5;
		memset(dp, 0, sizeof dp); 
		Mod[1] = 1 % n;
		ff(i, 2, 100) Mod[i] = (10 * Mod[i - 1]) % n;
		dp[max(cnt1, cnt2) + 1][Mod[max(cnt1, cnt2) + 1]] = 1;
		ff(i, max(cnt1, cnt2) + 2, 100) fo(j, 0, n) {
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][(j - Mod[i] + n) % n]);
		}
		int mx = -1, MOD = 0;
		bool flag = 0; string s = "";
		ff(i, max(cnt1, cnt2) + 1, 100) if (dp[i][0]) { mx = i; break; }
		if (mx == -1) { printf("BRAK\n"); continue; }
		while(mx > max(cnt1, cnt2) + 1) {
			if (dp[mx][MOD] == dp[mx - 1][(MOD - Mod[mx] + n) % n]) { s = s + "1"; MOD = (MOD - Mod[mx] + n) % n; mx--; continue; }
			else { s = s + "0"; mx--; continue; }
		}
		s = s + "1";
		ff(i, 1, max(cnt1, cnt2)) s = s + "0";
		printf("%s\n", s.c_str());
	}	
}