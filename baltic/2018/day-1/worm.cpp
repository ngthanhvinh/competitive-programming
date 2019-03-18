#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const double golden = 1.61803398875;

int cache[MAXN];
int cache2[1005][1005];
int N, M, K, Q;
int nquery;
int sub;

__attribute__((noreturn))
void guess(int x, int y, int z) {
	printf("! %d %d %d\n", x, y, z);
	exit(0);
}

int query(int x, int y, int z) {
	if (x == 0 || y == 0 || z == 0 || x == N + 1 || y == M + 1 || z == K + 1) return 0;
	if (sub == 1 && cache[x]) return cache[x];
	if (sub == 2 && cache2[x][y]) return cache2[x][y];

	++nquery;
	assert(nquery <= Q);
	printf("? %d %d %d\n", x, y, z);
	fflush(stdout);

	int ans = -1;
	(void)scanf("%d", &ans);
	if (ans == -1) exit(0);

	if (sub == 1) cache[x] = ans;
	else cache2[x][y] = ans;
	return ans;
}



namespace sub1 {
	void solve() {
		int low = 1, high = N;
		while(low < high) {
			//double rmid = (double)(low + high) / golden;
			//int mid = (int)rmid;

			int mid = ((low + high) >> 1);
			if (query(mid, 1, 1) <= query(mid + 1, 1, 1)) low = mid + 1;
			else high = mid;
		}

		guess(low, 1, 1);
	}
}

namespace sub2 {
	bool vis[1005][1005];
	const int dx[] = {0, 0, +1, -1};
	const int dy[] = {-1, +1, 0, 0};

	int max_row(int r) {
		int ret = 0;
		for (int i = 1; i <= M; ++i) ret = max(ret, query(r, i, 1));
		return ret;
	}

	void solve() {
		int low = 1, high = N;
		while(low < high) {
			int mid = ((low + high) >> 1);
			if (max_row(mid) <= max_row(mid + 1)) low = mid + 1;
			else high = mid;
		}

		for (int i = 1; i <= M; ++i) {
			int cur = query(low, i, 1);
			bool ok = true;
			for (int dir = 0; dir < 4; ++dir) {
				int x = low + dx[dir], y = i + dy[dir];
				if (query(x, y, 1) > cur) {
					ok = false;
					break;
				}
			}
			if (ok) {
				guess(low, i, 1);
			}
		}
	}
}

int main() {
	//srand(time(NULL));
	(void)scanf("%d %d %d %d", &N, &M, &K, &Q);
	//for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);

	if (M == 1 && K == 1) {
		sub = 1;
		sub1::solve();
	} else if (K == 1) {
		sub = 2;
		sub2::solve();
	} else {
		assert(0);
	}
}