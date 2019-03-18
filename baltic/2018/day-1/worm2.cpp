#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const double golden = 1.61803398875;

int cache[MAXN];
int N, M, K, Q;
int A[MAXN];
int nquery;
/*
int query(int x, int y, int z) {
	if (x == 0 || x == N + 1) return 0;
	if (cache[x]) return cache[x];
	printf("? %d %d %d\n", x, y, z);
	fflush(stdout);
	int ans = -1;
	(void)scanf("%d", &ans);
	if (ans == -1) exit(0);
	return cache[x] = ans;
}
*/

int query(int x, int y, int z) {
	if (x == 0 || x == N + 1) return 0;
	if (cache[x]) return cache[x];
	++nquery;
	//assert(nquery <= Q);
	int ans = A[x];
	return cache[x] = A[x];
}

__attribute__((noreturn))
void guess(int x, int y, int z) {
	cerr << "nquery: " << nquery << endl;
	printf("! %d %d %d\n", x, y, z);
	exit(0);
}

int main() {
	srand(time(NULL));
	(void)scanf("%d %d %d %d", &N, &M, &K, &Q);
	for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);

	assert(M == 1 && K == 1);
	
	int low = 1, high = N;
	while(low < high) {
		double rmid = (double)(low + high) / golden;
		int mid = (int)rmid;
		cerr << low << ' ' << high << ' ' << mid << endl;

		if (query(mid, 1, 1) <= query(mid + 1, 1, 1)) low = mid + 1;
		else high = mid;
	}

	guess(low, 1, 1);
}