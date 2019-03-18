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

const int INF = 1e9, N = 1000010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, k, a[N]; ll s[N], f[N][2];

int main() {
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin >> n >> k; ff(i, 1, n) { cin >> a[i]; s[i] = s[i - 1] + a[i]; }
	deque <ll> q;
	ff(i, 1, k - 1) {
		f[i][1] = s[i]; f[i][0] = max(f[i - 1][0], f[i - 1][1]);
		while(!q.empty() && q.back() < f[i][0] - s[i]) q.pop_back();
		q.push_back(f[i][0] - s[i]);
	}
	ff(i, k, n) {
		f[i][0] = max(f[i - 1][0], f[i - 1][1]);
		f[i][1] = q.front() + s[i]; //upd(1, 0, n, i, f[i][0] - s[i]);
		while(!q.empty() && q.back() < f[i][0] - s[i]) q.pop_back();
		if (!q.empty() && q.front() == f[i - k + 1][0] - s[i - k + 1]) q.pop_front();
		q.push_back(f[i][0] - s[i]);
	}
	printf("%lld\n", max(f[n][0], f[n][1]));
}