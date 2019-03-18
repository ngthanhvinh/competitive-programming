#include <bits/stdc++.h>
using namespace std;

const int MAXS = 2005;
const int MAXN = 20005;

int n, m, S;
int V[100005], W[100005], K[100005];
vector < pair<int,int> > vec[MAXS];
int dp[2][MAXN];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> S >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> V[i] >> W[i] >> K[i];
        vec[W[i]].push_back(make_pair(V[i], K[i]));
    }
    for (int w = 1; w <= S; ++w) {
        sort(vec[w].begin(), vec[w].end());
        int need = S / w;
        while(vec[w].size() && need) {
            vec[w].back().second--;
            need--;
            m++;
            V[m] = vec[w].back().first;
            W[m] = w;
            if (vec[w].back().second == 0) vec[w].pop_back();
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= S; ++j) {
            dp[1][j] = dp[0][j];
            if (j >= W[i]) dp[1][j] = max(dp[1][j], dp[0][j - W[i]] + V[i]);
        }
        for (int j = 0; j <= S; ++j) {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
    }

    int res = 0;
    for (int j = 0; j <= S; ++j) {
        res = max(res, dp[0][j]);
    }

    cout << res << '\n';
}