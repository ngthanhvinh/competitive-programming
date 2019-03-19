#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int n;
char a[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n-1; ++i) cin >> a[i];
	a[n] = '-';
	bool in = 0;
	for (int i = 1; i <= n; ++i) {
		if (in && a[i] == '-') { printf(")"); in = 0; }
		if (!in && a[i] == '+') { printf("("); in = 1; }
		if (i < n) printf("-");
	}
	printf("\n");
}