#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
typedef pair<long long, int> ii;

int n, a[maxn];
long long m, sum = 0, f[maxn], val[maxn];
int cur;
deque <int> q;
set <ii> s;

void noSolution() { cout << -1 << endl; exit(0); }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cur = 1;
	for (int i = 1; i <= n; i++) {
		sum += a[i];
		while(sum > m) sum -= a[cur], cur++;
		if (cur > i) noSolution();

		while(!q.empty() && q.front() < cur) s.erase(ii(val[q.front()], q.front())), val[q.front()] = 0, q.pop_front();
		if (!q.empty()) {
			int u = q.front(); s.erase(ii(val[u], u));
			val[u] = a[u] + f[cur-1]; s.insert(ii(val[u], u)); 
		}

		while(!q.empty() && a[q.back()] < a[i]) s.erase(ii(val[q.back()], q.back())), val[q.back()] = 0, q.pop_back();
		if (!q.empty()) val[i] = a[i] + f[q.back()]; else val[i] = a[i] + f[cur-1];

		q.push_back(i);
		s.insert(ii(val[i], i));

		f[i] = (s.begin()->first);
	}
	printf("%lld\n", f[n]);
}