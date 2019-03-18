#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;

int N, M;

struct BIT {
	int X[maxn];
	int T[maxn];
	int x(int a) { return lower_bound(X + 1, X + N + 1, a, greater<int>()) - X; }
	void add(int p) {
		for (int i = x(p); i <= N; i += i & (-i)) ++T[i];
	}
	int get(int p) {
		int i = upper_bound(X + 1, X + N + 1, p, greater<int>()) - X - 1;
		int ans = 0;
		//cout << p << ' ' << i << endl;
		for (; i; i -= i & (-i)) ans += T[i];
		//cout << p << ' ' << i << ' ' << ans << endl;
		return ans;
	}
} T;

ii A[maxn];
int X[maxn];
int two[maxn];

const int mod = 1e9 + 7;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M;
	two[0] = 1;
	for (int i = 1; i <= N; ++i) two[i] = 1LL * two[i - 1] * 2 % mod;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i].x >> A[i].y;
		T.X[i] = A[i].y;
	}
	sort(A  + 1, A + N + 1);
	sort(T.X + 1, T.X + N + 1, greater<int>());
	for (int i = 1; i <= M; ++i) cin >> X[i];
	sort(X + 1, X + M + 1);
	int ans = 0;
	for (int i = 1; i <= N; ++i) {
		int nx = lower_bound(X + 1, X + M + 1, A[i].x) - X;
		//cout << i << ' ' << A[i].x << ' ' << nx << endl;
		if (nx == M + 1 || X[nx] > A[i].y) continue;
		ans = (ans + two[T.get(X[nx])]) % mod;
		T.add(A[i].y);
	}
	cout << ans << endl;
}
