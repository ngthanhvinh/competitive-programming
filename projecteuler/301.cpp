#include <bits/stdc++.h>
using namespace std;

int main() {
	long long ans = 0;
	for (long long i = 1; i <= (1LL << 30); i++) {
		if ((i ^ (2 * i) ^ (3 * i)) == 0) ans++;
	}
	printf("%lld\n", ans);
}