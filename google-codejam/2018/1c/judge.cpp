#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest = 100;
	for (int itest = 1; itest <= ntest; ++itest) {
		system("./test > in");
		system("./c < in > out");
		system("./c_stress < in > ans");

		cout << "Test #" << itest << ": ";
		if (system("diff ans out") != 0) {
			cout << "WA!\n"; return 0;
		} else {
			cout << "AC!\n";
		}
 	}
}