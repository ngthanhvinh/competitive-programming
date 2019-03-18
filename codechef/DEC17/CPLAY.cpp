#include <bits/stdc++.h>
using namespace std;

string s;

void out(int team, int nMatch) {
	char c = team == 0 ? 'A' : 'B';
	printf("TEAM-%c %d\n", c, nMatch);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	while(cin >> s) {
		int score[2] = {0,0};
		bool ok = false;
		for (int nMatch = 0; nMatch < 10; ++nMatch) {
			int cur = (nMatch & 1);
			score[cur] += s[nMatch] - '0';
			// check whether one team can finish the match
			int test[2];
			// check whether team 0(A) can win
			test[0] = score[0]; test[1] = score[1];
			for (int nxtMatch = nMatch + 1; nxtMatch < 10; ++nxtMatch) {
				if (nxtMatch & 1) test[1]++;
			}
			if (test[0] > test[1]) { ok = true; out(0, nMatch + 1); break; }
			// check whether team 1(B) can win
			test[0] = score[0]; test[1] = score[1];
			for (int nxtMatch = nMatch + 1; nxtMatch < 10; ++nxtMatch) {
				if ((nxtMatch & 1) == 0) test[0]++;
			}
			if (test[1] > test[0]) { ok = true; out(1, nMatch + 1); break; }
		}
		if (ok) continue;
		// sudden death
		for (int nMatch = 10; nMatch < 20; nMatch += 2) {
			score[0] += s[nMatch] - '0';
			score[1] += s[nMatch + 1] - '0'; 
			if (score[0] > score[1]) { ok = true; out(0, nMatch + 2); break; }
			else if (score[1] > score[0]) { ok = true; out(1, nMatch + 2); break; }
		}
		if (!ok) printf("TIE\n");
	}
}