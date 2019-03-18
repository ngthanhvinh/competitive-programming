#include <bits/stdc++.h>
using namespace std;

string s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> s; int n = s.size();
		bool ok = 1;
		for (int i = 0; i < n/2; i++) {
			char a = s[i], b = s[n-i-1];
			if (a == '.' && b == '.') s[i] = 'a', s[n-1-i] = 'a';
			else if (a != '.' && b == '.') s[n-1-i] = a;
			else if (a == '.' && b != '.') s[i] = b;
			else if (a != '.' && b != '.' && a != b) { ok = 0; break; }
		}
		if (!ok) { cout << "-1" << endl; continue; }
		if (n % 2 == 1 && s[n/2] == '.') s[n/2] = 'a';
		cout << s << endl;
 	}
}