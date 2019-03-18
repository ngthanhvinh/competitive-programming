#include <bits/stdc++.h>
using namespace std;
const int NTEST = 100;
const string NAME = "scchem";

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    for (int i = 1; i <= NTEST; i++) {
        system((NAME + "_gen.exe").c_str());
        system((NAME + ".exe").c_str());
        system((NAME + "_trau.exe").c_str());

        if (system(("fc /w " + NAME + ".out " + NAME + ".ans").c_str()) != 0) {
            cout << "Test " << i << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << i << ": CORRECT!\n";
    }
}
