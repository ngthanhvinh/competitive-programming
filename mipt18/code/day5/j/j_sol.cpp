#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1005;

int N;
int A[maxn], B[maxn];
int d[maxn], c[maxn];
vector<ii> G[maxn];

int f(int v) {
	if (c[v]) return d[v];
	c[v] = 1;
	for (auto u: G[v]) 
		d[v] = max(d[v], f(u.y) + u.x);
	return d[v];
}

int step(int v) {
	if (v == 0) return 1;
	return step(v / 2) + 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	for (int i = 1; i <= N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			if (A[i] > A[j]) {
				G[A[j]].emplace_back(1, A[i]);
				//cout << A[j] << ' ' << A[i] << ' ' << 1 << endl;
			} else {
				G[A[i]].emplace_back(0, A[j]);
				//cout << A[i] << ' ' << A[j] << ' ' << 0 << endl;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= N; ++i) ans = max(ans, f(i));
	//for (int i = 1; i <= N; ++i) cout << d[i] << ' '; cout << endl;
	int steps = step(ans);
	printf("%d\n", steps - 1);
	while (steps--) {
		for (int i = 1; i <= N; ++i) printf("%d ", A[i]);
		printf("\n");
		vector<int> l, r;
		for (int i = 1; i <= N; ++i) {
			if (d[A[i]] & 1) l.push_back(i); else r.push_back(i);
			d[A[i]] /= 2;
		}
		int all = 0;
		for (auto u: l) B[++all] = A[u];
		for (auto u: r) B[++all] = A[u];
		for (int i = 1; i <= N; ++i) A[i] = B[i];
	}

}