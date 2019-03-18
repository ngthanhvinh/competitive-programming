#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
char a[N], b[N];
int T[N], n, m;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> (a+1) >> (b+1); n = strlen(a+1); m = strlen(b+1);
	T[0] = -1;
	for (int i = 1; i <= m; i++) {
		T[i] = 0;
		for (int j = T[i-1]; j != -1; j = T[j]) {
			if (b[j+1] == b[i]) { T[i] = j + 1; break; }
		}
		//cout << T[i] << ' ';
	}
	//cout << endl;
	int u = 0;
	for (int i = 1; i <= n; i++) {
		while(u != 0 && b[u+1] != a[i]) u = T[u];
		if (b[u+1] == a[i]) u++;
		if (u == m) printf("%d ", i - m + 1);  
	}
	printf("\n");
}