#include <bits/stdc++.h>
using namespace std;

int main() {
	int ntest = 100;
	for (int itest = 1; itest <= ntest; ++itest) {
		system("./atlarge_gen");
		system("./atlarge");
		system("./atlarge_buf");

		if (system("diff atlarge.out atlarge.ans") != 0) {
			cout << "Wrong Answer\n"; return 0;
		}
		cout << "Accepted\n";
	}
}