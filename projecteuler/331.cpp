#include <bits/stdc++.h>
using namespace std;

long long ans = 3;

bitset <1<<30> bs;
void prep(long long N) {
	bs.clear();
	for (int x = 0; x < N; ++x) {
		for (int y = ceil(sqrt((N - 1) * (N - 1) - x * x)); y <= sqrt(N * N - x * x); ++y) {
			
		}
	}
}

void solve(long long N) {

}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

}