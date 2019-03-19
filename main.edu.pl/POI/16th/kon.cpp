#include <bits/stdc++.h>
using namespace std;

void mxm(int &a, int b) { a = max(a, b); }

const int N = 610;
const int K = 51;

int n, k, x[N][N], s[N][N];
int f[N][K];

int get(int x, int y) {
	// (x,y+1) -> (y,n)
	if (x > y || y + 1 > n) return -1e9;
	return s[y][n] - s[x-1][n] - s[y][y] + s[x-1][y];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n - 1; ++i) {
		for (int j = i + 1; j <= n; ++j) cin >> x[i][j];
	}
	for (int i = 1; i <= n - 1; ++i) {
		for (int j = 1; j <= n; ++j) s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + x[i][j];
	}
	for (int i = 0; i <= n; ++i) for (int j = 0; j <= k; ++j) f[i][j] = -1e9;
	f[0][0] = 0;
	
	for (int i = 1; i <= n - 1; ++i) for (int j = 1; j <= k; ++j) {
		for (int prv = 0; prv < i; ++prv) mxm(f[i][j], f[prv][j-1] + get(prv + 1, i));
	}

	int ans = 0, cur = 0;
	for (int i = 1; i <= n - 1; ++i) if (ans < f[i][k]) ans = f[i][k], cur = i;

	vector <int> res;
	while(k) {
		res.push_back(cur);
		for (int j = 0; j < cur; ++j) if (f[cur][k] == f[j][k-1] + get(j + 1, cur)) {
			cur = j; --k;
			break;
		}
	}

	reverse(res.begin(), res.end());
	for (int i = 0; i < (int)res.size(); ++i) printf("%d ", res[i]); printf("\n");
}