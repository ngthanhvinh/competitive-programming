#include <bits/stdc++.h>
using namespace std;

string get(vector<string> &vec) {
    int ptr = 0;
    string ret = "";
    while(true) {
        char c = '~';
        for (auto &s : vec) {
            if (s.size() <= ptr) {
                continue;
            }
            if (c == '~') c = s[ptr];
            else if (c != s[ptr]) return "*";
        }
        if (c == '~') break;
        ret += c;
        ptr++;
    }
    return ret;
}

string solve() {
    int n; cin >> n;
    vector<string> s(n);
    vector<string> pre(n), suf(n);
    string tot = "";
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    for (int i = 0; i < n; ++i) {
        int l = 0;
        while(l < s[i].size() && s[i][l] != '*') {
            pre[i] += s[i][l];
            l++;
        }
        int r = s[i].size()-1;
        while(r >= 0 && s[i][r] != '*') {
            suf[i] += s[i][r];
            r--;
        }
        for (int j = l; j <= r; ++j) {
            if (s[i][j] != '*') {
                tot += s[i][j];
            }
        }
    }

    string lef = get(pre);
    string rig = get(suf);
    if (lef != "*" && rig != "*") {
        reverse(rig.begin(), rig.end());
        return lef + tot + rig;
    }
    return "*";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int ntest; cin >> ntest;
    for (int itest = 1; itest <= ntest; ++itest) {
        cout << "Case #" << itest << ": " << solve() << endl;
    }
}