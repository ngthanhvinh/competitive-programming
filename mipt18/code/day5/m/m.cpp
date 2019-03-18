#include <bits/stdc++.h>
using namespace std;

const int MAX_DIGIT = 19;
typedef pair<int,int> ii;

int cannot[] = {1, 2, 3, 5, 6, 9, 10, 13, 17};
int mn[7];
int x[MAX_DIGIT + 1];
map < vector<ii>, long long > f[MAX_DIGIT + 1][2];
long long A, B;
int k;

long long dp(int pos, int smaller, vector <ii> a) {
	// a contains all candidate carries with the form: {carry, min_need}
	if (a.empty()) {
		return 0;
	}
	if (f[pos][smaller].find(a) != f[pos][smaller].end()) {
		return f[pos][smaller][a];
	}
	if (pos == MAX_DIGIT) {
		if (!smaller) return 0;
		if (a.size() > 0 && a[0].first == 0 && a[0].second > 0) return 1;
		return 0;
	}

	// solve
	long long &ret = f[pos][smaller][a];

	int high = smaller ? 9 : x[pos + 1];

	for (int nxt = 0; nxt <= high; ++nxt) {
		for (int i = 0; i < 7; ++i) {
			mn[i] = 1e9;
		}

		for (auto &it : a) {
			int carry = it.first;
			int need = it.second;

			int c = carry * 10 + nxt;

			// find
			for (int i = need; i <= k; ++i) {
				for (int cnt4 = 0; cnt4 <= i; ++cnt4) {
					int cnt7 = i - cnt4;
					int new_carry = c - (4 * cnt4 + 7 * cnt7);
					if (new_carry < 0 || new_carry > 6) continue;

					mn[new_carry] = min(mn[new_carry], i);
				}
			}
		}

		// -> new state
		vector <ii> na;
		int nsmaller = smaller | (nxt < high);
		for (int new_carry = 0; new_carry < 7; ++new_carry) {
			if (mn[new_carry] != 1e9) {
				na.push_back({new_carry, mn[new_carry]});
			}
		}

		ret += dp(pos + 1, nsmaller, na);
	}
	
	return ret;
}

long long solve(long long X) { // < X
	if (k > 9) {
		long long res = X;
		for (int i = 0; i < 9; ++i) {
			if (X > cannot[i]) --res;
		}
		return res;
	}

	for (int i = MAX_DIGIT; i >= 1; --i) {
		x[i] = X % 10; X /= 10;
	}

	for (int i = 0; i <= MAX_DIGIT; ++i) {
		for (int j = 0; j < 2; ++j) {
			f[i][j].clear();
		}
	}

	vector <ii> start;
	start.push_back(ii(0, 0));

	return dp(0, 0, start);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> A >> B >> k;
	printf("%lld\n", solve(B + 1) - solve(A));
}