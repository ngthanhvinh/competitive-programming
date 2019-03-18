#include <iostream>
using namespace std;

int n;
const string s[] = {"LB", "MB", "UB", "LB", "MB", "UB", "SU", "SL"};
const int val[]  = {4,5,6,1,2,3,8,7};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n;
		int q = n / 8, r = n % 8; if (!r) r = 8, q--;
		cout << 8 * q + val[r-1] << s[r-1] << endl;
	}	
}