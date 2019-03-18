#include <bits/stdc++.h>
using namespace std;

int n;
int g0[] = {0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 0, 5, 2, 2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 2, 7, 4};
int g1[] = {0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4}; 
int g[] = {8, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 9, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	while(cin >> n) {
		if (n / 34 == 0) (g0[n]) ? printf("White\n") : printf("Black\n");
		else if (n / 34 == 1) { n -= 34; (g1[n]) ? printf("White\n") : printf("Black\n"); }
		else { n %= 34; (g[n]) ? printf("White\n") : printf("Black\n"); }
	}
}