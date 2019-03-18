#include <iostream>
#include <cstdio>
using namespace std;

int n;
string s[2][110];

int cnt(string str, int a) {
    int res = 0;
    for (int i = 0; i < str.size(); ++i) res += (str[i] == 'a' + a);
    return res;
}

int main() {
    freopen("blocks.in", "r", stdin);
    freopen("blocks.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[0][i] >> s[1][i];
    for (int i = 0; i <= 25; ++i) {
        int ans = 0;
        for (int j = 1; j <= n; ++j) {
            ans += max(cnt(s[0][j], i), cnt(s[1][j], i));
        }
        cout << ans << endl;
    }
}
