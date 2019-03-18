#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
int X, Y, Z, A, B, C;

int f(int chooseC) {
	if (chooseC > X || chooseC < 0) return inf;
	int res = 0;
	res += chooseC * C;
	int x = X - chooseC, y = Y - chooseC, z = Z - chooseC; // update x, y, z

	// use only B
	res += x * B; // x will be 0 after processing
	int gap = min(x, z - y);
	x -= gap; z -= gap;
	int xz = x / 2, xy = x - xz;
	z -= xz, y -= xy;

	res += y * B; // y will be 0 after processing
	z -= y;

	// use only A for z
	res += z * A;
	return res;
}

void solve() {
	cin >> X >> Y >> Z >> A >> B >> C;
	int ans = inf;
	B = min(B, 2 * A);
	if (X > Y) swap(X, Y);
	if (X > Z) swap(X, Z);
	if (Y > Z) swap(Y, Z);

	for (int x = 0; x <= 10; ++x) {
		int chooseC = X - x;
		ans = min(ans, f(chooseC));
	}
	for (int x = Z - Y - 10; x <= Z - Y + 10; ++x) {
		int chooseC = X - x;
		ans = min(ans, f(chooseC));
	}
	for (int x = X; x >= X - 10; --x) {
		int chooseC = X - x;
		ans = min(ans, f(chooseC));
	}
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	while(tt--) {
		solve();
	}
}