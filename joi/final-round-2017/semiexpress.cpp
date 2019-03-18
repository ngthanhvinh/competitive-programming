#include <bits/stdc++.h>
using namespace std;
 
typedef pair<long long,long long> ii;
typedef pair<long long, ii> II;
 
const long long N = 3005;
 
long long n, m, k;
long long A, B, C, T;
long long s[N];
long long ans;
priority_queue <II> q;
 
void update(long long seg, long long posC) {
	if (posC >= s[seg + 1]) return;
	long long left = T - 1ll * s[seg] * B - 1ll * (posC - s[seg]) * C;
	if (left < 0) return;
 
	long long add = min((long long)(left / A) + 1, s[seg + 1] - posC);
	if (add > 0) q.push(II(add, ii(seg, posC + add))); 
}
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	cin >> A >> B >> C;
	cin >> T;
	for (long long i = 1; i <= m; ++i) cin >> s[i], --s[i];
 
	for (long long i = 2; i <= m; ++i) if (1ll * B * s[i] <= T) ++ans;
 
	for (long long i = 1; i < m; ++i) {
		long long left = T - 1ll * B * s[i];
		if (left < 0) continue;
 
		long long posC = s[i] + left / A + 1;
		ans += max(0LL, min(left / A, s[i + 1] - s[i] - 1));
 
		update(i, posC);
	}
	
	k -= m;
	while(k-- > 0 && !q.empty()) {
		II TOP = q.top(); q.pop();
		ans += TOP.first;
		long long seg = TOP.second.first, posC = TOP.second.second;
 
		update(seg, posC);
	}
 
	cout << ans << endl;
}