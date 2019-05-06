#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int tt = 10; cout << tt << endl;
	while(tt--) {
		int n = 1000;
		cout << n << ' ' << 30 << endl;
		for (int i = 1; i <= n; ++i) {
			cout << rand() % 1000 << ' '; 
		}
		cout << endl;
		for (int i = 1; i <= n; ++i) {
			cout << rand() % 1000 << ' '; 
		}
		cout << endl;
	}
}