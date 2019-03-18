#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;

int N;
ll A[maxn];

bool check(int La, int Lb) {
	for (int i = 2; i <= N; ++i)
		if (A[i] * Lb / La == A[i] * Lb / (La + A[1] * Lb)) return 0;
	return 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
	}
	sort(A + 1, A + N + 1);
	ll ans = 0;
	ii maxL(0, 1);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= 45000 && A[i] * maxL.y > 1LL * j * maxL.x; ++j) {
			if (check(A[i], j)) maxL = ii(A[i], j);
		}
	}
	//cout << maxL.x << ' ' << maxL.y << endl;
	for (int i = 2; i <= N; ++i) ans += A[i] * maxL.y / (maxL.x + A[1] * maxL.y);
	cout << ans << endl;
}