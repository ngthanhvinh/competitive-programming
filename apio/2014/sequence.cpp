#include <bits/stdc++.h>
using namespace std;
 
struct line {
	long long a; long long b; int id;
	line(long long a=0, long long b=0, int id=0): a(a), b(b), id(id) {}
} L[100005];
double X[100005];
int cur, szL, szX;
 
double intersect(line p, line q) {
	return (double)(p.b - q.b) / (q.a - p.a);
}
 
void add(long long a, long long b, int id) {
	line d = line(a, b, id);
	if (szL > 0 && L[szL].a == d.a) {
		if (L[szL].b <= d.b) return; 
		else {
			--szL; if (szX > 0) --szX;
		}
	}
	while(szL >= 2) {
		double curX = intersect(d, L[szL-1]);
		if (curX < X[szX]) --szX, --szL; else break;
	}
	if (szL > 0) {
		double curX = intersect(d, L[szL]);
		X[++szX] = curX;
	}
	L[++szL] = d;
}
 
pair<long long, int> get(long long x) {
	if (cur > szL) cur = szL;
	while(cur < szL && L[cur].a * x + L[cur].b > L[cur+1].a * x + L[cur+1].b) ++cur;
	return make_pair(L[cur].a * x + L[cur].b, L[cur].id);
}
 
const int N = 1e5 + 5, K = 205;
const long long inf = 1e18;
 
int n, k;
long long a[N];
long long f[N][2];
int trace[N][K];
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	scanf("%d %d", &n, &k); ++k;
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]), a[i] += a[i-1];
 
	for (int i = 0; i <= n; ++i) f[i][0] = inf;
	f[0][0] = 0;
 
	for (int j = 1; j <= k; ++j) {
		szL = szX = 0; cur = 1;
		add(0, f[0][0], 0);
		for (int i = 1; i <= n; ++i) {
			f[i][1] = inf;
			pair<long long, int> res = get(a[i]);
			if (f[i][1] > res.first + a[i] * a[i]){
				trace[i][j] = res.second;
				f[i][1] = res.first + a[i] * a[i];
			}
			add(-2 * a[i], f[i][0] + a[i] * a[i], i);
			f[i][0] = f[i][1];
		}
		f[0][0] = inf;
	}
 
	long long ans = f[n][0];
	ans = (a[n] * a[n] - ans) / 2;
 
	printf("%lld\n", ans);
	vector<int> vec;
	while(n) {
		n = trace[n][k]; --k;
		vec.push_back(n);
	}
	vec.pop_back();
	for (int i = vec.size()-1; i >= 0; --i) printf("%d ", vec[i]); printf("\n");
}