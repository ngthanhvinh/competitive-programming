#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int n, m;
char a[N][N];

int numStar(int x, int y, int k) {
    int ans = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (abs(i-x) + abs(j-y) <= k && a[i][j] == '*') ++ans;
    return ans;
}

int main() {
    freopen("rbull.inp", "r", stdin);
    freopen("rbull.ans", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j];
    /*
    int x, y, k;
    while(cin >> x >> y >> k) {
        cout << numStar(x,y,k) << endl;
    }
    */
    cerr << numStar(3,2,1) << endl;
}
