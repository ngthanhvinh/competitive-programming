/*
	Task: Temperature
	http://main.edu.pl/en/archive/oi/18/tem
*/

#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> ii;
#define ff(i, a, b) for (int i = a; i <= b; i++)
#define fi first
#define se second

const int N = 1000010;

int n; ii a[N];
int last;
int ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; ff(i, 1, n) cin >> a[i].fi >> a[i].se;
	priority_queue <ii> q;
	ff(i, 1, n) {
		//cout << "working on..." << i << ' ' << a[i].fi << ' ' << a[i].se << "\n";
		while(!q.empty() && (q.top().fi > a[i].se || q.top().se < last)) { last = max(last, q.top().se); q.pop(); }
		q.push(ii(a[i].fi, i));
		ans = max(ans, i - last);
	}
	printf("%d\n", ans);
}