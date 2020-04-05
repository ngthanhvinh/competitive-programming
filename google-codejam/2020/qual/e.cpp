#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int n;
int a[N][N];
bool checkRow[N][N];
bool checkCol[N][N];

void out() {
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         if (!checkRow[i][j]) return false;
    //         if (!checkCol[i][j]) return false;
    //     }
    // }

    int trace = 0;
    for (int i = 0; i < n; ++i) trace += a[i][i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << a[i][j] << ' ';
        cout << endl;
    }
    cout << "Trace = " << trace << endl;
    cout << "----------------\n";
}

void backtrack(int r, int c) {
    if (r == n) {
        out();
        return;
    }
    for (int v = 1; v <= n; ++v) {
        if (checkRow[r][v] || checkCol[c][v]) {
            continue;
        }
        a[r][c] = v;
        checkRow[r][v] = true;
        checkCol[c][v] = true;
        backtrack((c == n-1) ? (r+1) : r, (c == n-1) ? 0 : (c+1));
        a[r][c] = 0;
        checkRow[r][v] = false;
        checkCol[c][v] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    n = 5;
    backtrack(0, 0);
}