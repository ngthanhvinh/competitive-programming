#include <iostream>
#include <map>
#include <cstdio>
using namespace std;

const int N = 200010;

int n;
string city, state;
map < pair<string,string>, int > mp;
long long ans;

int main() {
    freopen("citystate.in", "r", stdin);
    freopen("citystate.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> city >> state;
        string c = ""; c += city[0]; c += city[1];
        mp[ make_pair(c, state) ]++;
    }
    for (map < pair<string,string>, int > :: iterator it = mp.begin(); it != mp.end(); ++it) {
        string f = (it->first).first, s = (it->first).second;
        if (mp.count( make_pair(s, f) )) {
            if (s != f) ans += 1ll * (it->second) * mp[ make_pair(s,f) ];
        }
    }
    cout << ans / 2 << endl;
}
