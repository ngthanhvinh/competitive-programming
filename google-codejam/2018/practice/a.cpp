#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	while(tt--) {
		int low, high, n; cin >> low >> high >> n;
		++low;
		bool found = false;
		while(low < high) {
			int mid = ((low + high) >> 1);
			cout << mid << endl; // guess
			string reply;
			cin >> reply; // reply
			if (reply == "CORRECT") {
				found = true;
				break;
			}
			else if (reply == "TOO_BIG") {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		if (!found) {
			cout << low << endl;
			string reply; cin >> reply; // obviously "CORRECT"
		}
	}
}