#include <bits/stdc++.h>
using namespace std;

string s;

void solve() {
    cin >> s;
    string res = "";
    int depth = 0;
    for (auto &c : s) {
        int v = c - '0';
        if (depth < v) {
            while(depth++ < v) res += '(';
        }
        else if (depth > v) {
            while(depth-- > v) res += ')';
        }
        res += c;
        depth = v;
    }
    while(depth--) res += ')';
    cout << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int ntest; cin >> ntest;
    for (int itest = 1; itest <= ntest; ++itest) {
        cout << "Case #" << itest << ": ";
        solve();
    }
}