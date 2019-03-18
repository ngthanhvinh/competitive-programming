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

int n, k, a[N];

void solve() {
	deque <int> q;
	cin >> n >> k; ff(i, 1, n) cin >> a[i];
	ff(i, 1, k - 1) {
		while(!q.empty() && q.back() > a[i]) q.pop_back();
		q.push_back(a[i]);
	}
	ff(i, k, n) {
		while(!q.empty() && q.back() > a[i]) q.pop_back();
		if (!q.empty() && q.front() == a[i - k]) q.pop_front();
		q.push_back(a[i]);
		printf("%d ", q.front());
	}
	printf("\n");
} 

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t; while(t--) solve();
}