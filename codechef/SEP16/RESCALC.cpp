#include <bits/stdc++.h>
using namespace std;

int n, t;
int cnt[7];
int mx;
int who;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> t;
	while(t--) {
		cin >> n; mx = 0; who = 0;
		for (int i = 1; i <= n; i++) {
			int c; cin >> c;
			memset(cnt, 0, sizeof cnt);
			for (int j = 1; j <= c; j++) { int type; cin >> type; cnt[type]++; }

			int res = 6;
			while(res >= 4) {
				res = 0;
				for (int j = 1; j <= 6; j++) if (cnt[j]) ++res;
				for (int j = 1; j <= 6; j++) if (cnt[j]) cnt[j]--;
				if (res == 6) c += 4;
				else if (res == 5) c += 2;
				else if (res == 4) c += 1;
 			}

			if (c > mx) mx = c, who = i;
			else if (c == mx) who = -1;
		}

		if (who == 1) cout << "chef" << endl;
		else if (who == -1) cout << "tie" << endl;
		else cout << who << endl;
	}
}