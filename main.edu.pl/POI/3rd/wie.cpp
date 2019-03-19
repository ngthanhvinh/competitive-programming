#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <cstdlib>
using namespace std;
const int N = 3010;
typedef pair<int,int> ii;

int n;
int x[2][N], y[2][N];
int pos[N], ansX[N], ansY[N];
vector <int> L[N], R[N];

void noSol() { cout << "NIE" << endl; exit(0); }

void solve(int a[2][N]) {
    set <ii> s;
    for (int i = 1; i <= n; ++i) L[i].clear(), R[i].clear();
    for (int i = 1; i <= n; ++i) L[a[0][i]].push_back(i), R[a[1][i]].push_back(i);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < R[i-1].size(); ++j) s.erase(ii(i-1, R[i-1][j]));
        for (int j = 0; j < L[i].size(); ++j) s.insert(ii(a[1][L[i][j]], L[i][j]));
        if (s.empty()) noSol();
        else {
            ii cur = (*s.begin()); s.erase(s.begin());
            pos[cur.second] = i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[0][i] >> y[0][i] >> x[1][i] >> y[1][i];
    solve(x); for (int i = 1; i <= n; ++i) ansX[i] = pos[i];
    solve(y); for (int i = 1; i <= n; ++i) ansY[i] = pos[i];

    for (int i = 1; i <= n; ++i) cout << ansX[i] << ' ' << ansY[i] << endl;
}
