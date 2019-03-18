#include <bits/stdc++.h>
using namespace std;

const int N = 8000000, mod = 500500507;
bool pr[N];
vector <int> prime;

void sieve() {
	pr[0] = pr[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!pr[i]) { prime.push_back(i); for (int j = i + i; j < N; j += i) pr[j] = 1; }
	}
}

int n;
int a[N];
double Log[N];
int pw[N];

int Pow(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; i++) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod; 
	}
	return res;
}

int main() {
	//freopen("500.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	cin >> n;
	int m = prime.size();
	for (int i = 0; i < m; i++) Log[i] = (double)log10(prime[i]);
	pw[0] = 1; for (int i = 1; i <= 10; ++i) pw[i] = pw[i-1] * 2;
	int start = 0;
	for (int i = 1; i <= n; i++) {
		int mn = 1e9;
		for (int j = 0; j < m; j++) {
			if (a[j]) mn = min(a[j], mn); 
			if (a[j] <= 1) break; 
		}
		if (mn == 1e9) mn = 0;
		double Min = 1e9; int pos = 0;
		for (int j = 0; j < m; j++) {
			double res;
			if (prime[j] > 3000) break;
			if (!a[j]) { break; }
			res = (double)Log[j] * pw[a[j] - mn];
			if (res < Min) { Min = res; pos = j; }
		}
		if (a[pos] >= 5) { a[start]++; start++; continue; }  
		else {
			if ((double)Log[pos] * pw[a[pos]] < (double)Log[start]) a[pos]++;
			else { a[start]++; start++; }
		}
	}
	int ans = 1; 
	for (int j = 0; j < m; j++) {
		if (!a[j]) break;
		for (int i = 0; i < a[j]; i++) ans = (1LL * ans * Pow(prime[j], pw[i])) % mod;
	}
	cout << ans << "\n";
}