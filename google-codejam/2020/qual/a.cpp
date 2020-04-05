#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int n;
int a[N][N];

bool check(vector<int> &cur) {
    vector <bool> was(n + 1);
    for (auto &v : cur) {
        if (was[v]) return true;
        else was[v] = true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    int ntest; cin >> ntest;
    for (int itest = 1; itest <= ntest; ++itest) {
        printf("Case #%d: ", itest);
        cin >> n;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                cin >> a[i][j];
        
        int trace = 0;
        for (int i = 1; i <= n; ++i) trace += a[i][i];

        int nrow = 0;
        for (int i = 1; i <= n; ++i) {
            vector<int> cur;
            for (int j = 1; j <= n; ++j) cur.push_back(a[i][j]);
            nrow += check(cur);
        }

        int ncol = 0;
        for (int j = 1; j <= n; ++j) {
            vector<int> cur;
            for (int i = 1; i <= n; ++i) cur.push_back(a[i][j]);
            ncol += check(cur);
        }
        
        printf("%d %d %d\n", trace, nrow, ncol);
    }
}