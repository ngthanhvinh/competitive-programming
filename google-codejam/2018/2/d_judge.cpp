#include <bits/stdc++.h>
using namespace std;

int main() {
	int ntest = 400;
	for (int i = 1; i <= ntest; ++i) {
		cerr << i << endl;
		system("./d_gen > in");
		system("./d_sol < in > ans");
		system("./d < in > out");
		if (system("diff out ans") != 0) {
			cerr << "Found!\n";
			return 0;
		}
	}
}