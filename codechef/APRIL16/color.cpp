#include <bits/stdc++.h>
using namespace std;

int n; string s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> s;
		int B = 0, G = 0, R = 0;
		for (int i = 0; i < s.size(); ++i) if (s[i] != 'B') ++B;
		for (int i = 0; i < s.size(); ++i) if (s[i] != 'G') ++G;
		for (int i = 0; i < s.size(); ++i) if (s[i] != 'R') ++R;
		cout << min(B, min(G, R)) << endl;
	}
}