#include <bits/stdc++.h>
using namespace std;

int x[505], y[505];
char dir[505];

const int MAX = 100005;
int leftX[MAX], rightX[MAX], downY[MAX], upY[MAX];
int W[MAX], S[MAX], E[MAX], N[MAX];

void solve() {
	int n, Q;
	cin >> n >> Q;

	memset(leftX, 0, sizeof leftX);
	memset(rightX, 0, sizeof rightX);
	memset(downY, 0, sizeof downY);
	memset(upY, 0, sizeof upY);
	memset(W, 0, sizeof W);
	memset(S, 0, sizeof S);
	memset(E, 0, sizeof E);
	memset(N, 0, sizeof N);

	for (int i = 1; i <= n; ++i) {
		cin >> x[i] >> y[i] >> dir[i];
		if (dir[i] == 'W') W[x[i]]++;
		if (dir[i] == 'E') E[x[i]]++;
		if (dir[i] == 'N') N[y[i]]++;
		if (dir[i] == 'S') S[y[i]]++;
	}

	for (int X = 0; X <= Q; ++X) {
		if (X > 0) leftX[X] = leftX[X - 1] + E[X - 1];
	}
	for (int X = Q; X >= 0; --X) {
		if (X < Q) rightX[X] = rightX[X + 1] + W[X + 1];
	}
	for (int Y = 0; Y <= Q; ++Y) {
		if (Y > 0) downY[Y] = downY[Y - 1] + N[Y - 1];
	}
	for (int Y = Q; Y >= 0; --Y) {
		if (Y < Q) upY[Y] = upY[Y + 1] + S[Y + 1];
	}

	int bestX = 0;
	for (int X = 0; X <= Q; ++X) {
		if (leftX[X] + rightX[X] > leftX[bestX] + rightX[bestX]) bestX = X;
	}
	int bestY = 0;
	for (int Y = 0; Y <= Q; ++Y) {
		if (downY[Y] + upY[Y] > downY[bestY] + upY[bestY]) bestY = Y;
	}

	cout << bestX << ' ' << bestY << endl;
//	cerr << leftX[bestX] + rightX[bestX] << ' ' << upY[bestY] + downY[bestY] << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		solve();
	}
}