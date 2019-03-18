#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "w", stdout);
	srand(time(NULL));
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt = 100;
	cout << tt << endl;
	while(tt--) {
		cout << rand() % 100 + 1 << ' ' << rand() % 100 + 1 << ' ' << rand() % 100 + 1 << ' ';
		cout << rand() % 1000 + 1 << ' ' << rand() % 1000 + 1 << ' ' << rand() % 1000 + 1 << endl;
	}
}