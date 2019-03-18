#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 1005;

int n, m;
int a[N][N];

struct query {
    int x; int y; int r; int c;
    query(int x=0, int y=0, int r=0, int c=0): x(x), y(y), r(r), c(c) {}
};

vector <query> ans;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) { char c; cin >> c; a[i][j] = c - '0'; }

    for (int i = 1; i <= n; ++i) {
        int nFlip = 0;
        for (int j = 1; j <= m; ++j) {
            int x = a[i][j] ^ nFlip;
            if (x != a[i+1][j]) {
                nFlip ^= 1;
                ans.push_back(query(1, j, i, m - j + 1));
            }
        }
    }

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) printf("%d %d %d %d\n", ans[i].x, ans[i].y, ans[i].r, ans[i].c);
}
