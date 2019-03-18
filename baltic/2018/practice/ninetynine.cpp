#include <bits/stdc++.h>
using namespace std;

bool f[100];
int s;

void upd() {
	int reply; cin >> reply;
	s = reply;
	if (s == 99) assert(0); // false
}

int main() {
	ios_base::sync_with_stdio(false);
	f[99] = false; // lose
	for (int i = 98; i >= 1; --i) {
		f[i] = false;
		for (int j = 1; j <= 2; ++j) {
			int k = i + j;
			if (k <= 99) f[i] |= (f[k] == 0);
		}
	}

	s = 1;
	cout << s << endl;

	while(true) {
		upd();
		if (f[s]) {
			for (int j = 1; j <= 2; ++j) {
				int k = s + j;
				if (k <= 99 && !f[k]) {
					s += j;
					cout << s << endl;
					if (s == 99) exit(0);
					break;
				}
			}
		}
		else {
			int r = rand() % 2 + 1;
			s += r;
			cout << s << endl;
		}
	}
}