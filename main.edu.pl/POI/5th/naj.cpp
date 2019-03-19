#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;

int n, k;
int a[27];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= k; ++i) cin >> a[i]; // weights
	sort(a + 1, a + k + 1);

	multiset <long long> s;
	multiset <long long>::iterator iter;
	s.insert(0);

	long long sum = 0, mn = inf;

	while(s.size() <= n && sum < mn) {
		if (s.size() == n) mn = sum;
		iter = s.begin(); 
		long long t = (*iter); s.erase(iter); // the smallest element
		sum -= t;

		for (int i = 1; i <= k; ++i) {
			s.insert(t + a[i]); // add one more character
			sum += t + a[i];
		}
		while(s.size() > n) {
			iter = s.end(); --iter;
			t = (*iter); // the largest element -> pop
			s.erase(iter);
			sum -= t;
		}
	}

	cout << mn << endl;
}