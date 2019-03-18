#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	cout << "1\n"; cout << flush;
	cout << "4 1 1 2 3\n"; cout << flush; 
	cout << "4 4 4 3 5\n"; cout << flush;
	int ans; cin >> ans;
	cout << "2\n"; cout << flush;
	if (ans == -1) cout << "5\n";
	else if (ans == -2) cout << "4\n";
	else if (ans == 0) cout << "3\n";
	else if (ans == 1) cout << "2\n";
	else cout << "1\n";
	cout << flush;
	exit(0);
}