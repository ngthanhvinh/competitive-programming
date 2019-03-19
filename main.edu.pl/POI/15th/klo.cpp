#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

const int N = 100010, MAX = 1000010;

int n, k, a[N];
int cnt[MAX];
set <int> s;
long long ans = 1e18;
long long sum[N];
int median, to, cur;

int b0; long long bsum;

int get(int x) { if (x == cur) return b0; else if (x < cur) return b0 - cnt[cur]; else return b0 + cnt[x]; }
long long getsum(int x) { if (x == cur) return bsum; else if (x < cur) return bsum - 1ll * cnt[cur] * cur; else return bsum + 1ll * cnt[x] * x; }

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), sum[i] = sum[i-1] + a[i];
	for (int i = 1; i <= k; ++i) ++cnt[a[i]], s.insert(a[i]);
	int r = 0;
	for (int i = 0; i < MAX; ++i) { r += cnt[i]; if (2 * r >= k) { cur = i; break; } }
	ans = 0; to = k; median = cur;
	for (int i = 1; i <= k; ++i) { ans += abs(a[i] - cur); if (a[i] <= cur) b0++, bsum += a[i]; } 

	for (int i = k+1; i <= n; ++i) {
		cnt[a[i-k]]--; if (!cnt[a[i-k]]) s.erase(a[i-k]); if (a[i-k] <= cur) b0--, bsum -= a[i-k];
		cnt[a[i]]++; if (cnt[a[i]] == 1) s.insert(a[i]); if (a[i] <= cur) b0++, bsum += a[i];

		set <int>::iterator it = s.lower_bound(cur);
		int newCur = 1e9;
		if (2 * get(cur) >= k) newCur = cur;
		if (it != s.end()) {
			int t = (*it); if (2 * get(t) >= k) newCur = min(newCur, t);
		}
		if ((*it) == cur && it != s.begin()) {
			--it; int t = (*it); if (2 * get(t) >= k) newCur = min(newCur, t); ++it;
		}
		set <int>::iterator ITEND = s.end(); ITEND--;
		if (it != ITEND && it != s.end()) {
			++it; int t = (*it); if (2 * get(t) >= k) newCur = min(newCur, t); --it;
		}

		int b = get(newCur); b0 = b; long long bs = getsum(newCur); bsum = bs;
		cur = newCur;
		long long res = 1ll * (2 * b - k) * cur + (sum[i] - sum[i-k]) - 2ll * bs;
		if (ans > res) ans = res, median = cur, to = i;
	}

	printf("%lld\n", ans);
	for (int i = 1; i <= n; ++i) {
		if (i >= to-k+1 && i <= to) printf("%d\n", median);
		else printf("%d\n", a[i]);
	}
}