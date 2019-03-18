#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, a[N], b[N];
int T[N];
bool used[N];

void upd(int x) { for(; x < N; x += x & -x) T[x]++; }
int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += T[x]; return res; }

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", b + i);

	int l = 1, r = 2 * n - 1;
	int pt = 0;
	for (int i = 1; i <= n; ++i) {
		if (!used[b[i]]) used[b[i]] = 1, a[++pt] = b[i], upd(b[i]);

		int med = b[i];
		while(pt < 2 * i - 1) {
			while(l <= 2 * n - 1 && used[l]) ++l;
			while(r >= 1 && used[r]) --r;
			int smaller = get(med - 1);
			if (smaller < i - 1) a[++pt] = l, upd(l), used[l++] = 1;
			else if (pt - smaller < i) a[++pt] = r, upd(r), used[r--] = 1;
		}
	}

	for (int i = 1; i <= 2 * n - 1; ++i) printf("%d ", a[i]);
	printf("\n");
}