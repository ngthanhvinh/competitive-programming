#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "w", stdout); srand(time(NULL));
    int n = rand() % 1000 + 1, k = rand() % 10 + 1;
    cout << n << ' ' << k << endl;
    for (int i = 0; i < n; i++) cout << rand() % 1000 + 1 << endl;
}
