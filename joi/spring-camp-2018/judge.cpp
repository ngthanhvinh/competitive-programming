#include <bits/stdc++.h>
using namespace std;

const int NTEST = 300;

int main() {
	for (int itest = 1; itest <= NTEST; ++itest) {
		system("./test");
		system("./candies < in > out");
		system("./candies_stress < in > ans");
		if (system("diff out ans") != 0) {
			cout << "Test " << itest << ": Wrong Answer!\n";
			return 0;
		} else {
			cout << "Test " << itest << ": Accepted!\n";
		}
	}
}