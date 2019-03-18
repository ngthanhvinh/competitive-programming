#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	while(t--) {
		string s; cin >> s;
		int cnt = 0;
		for (int i = 0; i < s.size(); i++) cnt += (s[i] == '0');
		if (cnt == 1 || cnt == s.size()-1) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}