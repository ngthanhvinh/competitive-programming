#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int k, n;
int sz;
long long ans;
pair<int,int> a[N];
vector<int> z;
vector<int> Q[N];

long long solve1() {
	if (n == 0) return 0;
	long long res = 0;
	int med = z[z.size() / 2];
	for (int i = 0; i < z.size(); ++i) {
		res += abs(med - z[i]);
	}
	return res;
}

long long fl[N];
long long fr[N];
int T[N];
long long sum[N];

void upd(int x) { for (; x < N; x += x & -x) T[x]++; }
int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += T[x]; return res; }
void upd_sum(int x, int v) { for (; x < N; x += x & -x) sum[x] += v; }
long long get_sum(int x) { long long res = 0; for (; x > 0; x -= x & -x) res += sum[x]; return res; }

void prepare(int id) {
	long long cur = 0;
	memset(T, 0, sizeof T);
	memset(sum, 0, sizeof sum);

	for (int i = 1; i <= n; ++i) {
		int s = lower_bound(z.begin(), z.end(), a[i].first) - z.begin() + 1;
		int t = lower_bound(z.begin(), z.end(), a[i].second) - z.begin() + 1;
		upd(s); upd(t);
		upd_sum(s, a[i].first); upd_sum(t, a[i].second);
		cur += a[i].first; cur += a[i].second;

		int l = 1, r = z.size();
		while(l < r) {
			int mid = ((l + r) >> 1);
			if (get(mid) >= i) r = mid; else l = mid + 1;
		}
		int smaller = get(l);
		long long	cur_sum = get_sum(l);
		
		long long res = ((cur - cur_sum) - 1LL * (2 * i - smaller) * z[l-1]) + (1LL * smaller * z[l-1] - cur_sum);
		if (!id) fl[i] = res; else fr[n + 1 - i] = res;
	}
}

long long solve2() {
	if (n == 0) return 0;

	sort(a + 1, a + n + 1, [&](pair<int,int> x, pair<int,int> y) {
		return x.first + x.second < y.first + y.second;
	});

	prepare(0); reverse(a + 1, a + n + 1); prepare(1);

	long long res = 1e18;
	for (int i = 1; i <= n; ++i) {
		res = min(res, fl[i] + fr[i + 1]);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> k >> n;
	for (int i = 1; i <= n; ++i) {
		char p, q;
		int s, t;
		cin >> p >> s >> q >> t;
		if (p == q) ans += abs(s - t);
		else ++sz, a[sz] = make_pair(min(s, t), max(s, t));
	}
	n = sz;
	for (int i = 1; i <= n; ++i) {
		z.push_back(a[i].first);
		z.push_back(a[i].second);
	}
	sort(z.begin(), z.end());

	ans += n;
	if (k == 1) ans += solve1(); else ans += min(solve1(), solve2());

	printf("%lld\n", ans);
}