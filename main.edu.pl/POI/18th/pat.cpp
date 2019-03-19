#include <bits/stdc++.h>
using namespace std;
const int N = 51;
typedef pair<int,int> ii;
#define fi first
#define se second
#define ff(i, a, b) for (int i = a; i <= b; i++)

int n;
vector <ii> a;
int Max[N];

int main() {
    cin >> n; memset(Max, -1, sizeof Max);
    for (int i = 1; i <= n; i++) {
        int val; cin >> val;
        while(val--) { int x; cin >> x; a.push_back(ii(x, i)); }
    }
    sort(a.begin(), a.end());
    //ff(i, 0, a.size()-1) cout << a[i].fi << ' ' << a[i].se << "\n";
    ff(i, 0, a.size()-1) {
        int v = a[i].fi, color = a[i].se;
        //cout << v << ' ' << color << "\n";
        Max[color] = max(Max[color], v);
       // cout << "Max color: " << Max[color] << endl;
        int Mx1 = -1, curMax1 = 0;
        int Mx2 = -1, curMax2 = 0;
        for (int j = 1; j <= n; j++)
            if (j != color && Mx1 < Max[j]) { Mx1 = Max[j]; curMax1 = j; }
        for (int j = 1; j <= n; j++)
            if (j != color && j != curMax1 && Mx2 < Max[j]) { Mx2 = Max[j]; curMax2 = j; }
        if (Mx1 != -1 && Mx2 != -1 && Mx1 + Mx2 > v) {
            cout << color << ' ' << v << ' ';
            cout << curMax1 << ' ' << Mx1 << ' ';
            cout << curMax2 << ' ' << Mx2 << "\n";
            return 0;
        }
    }
    cout << "NIE\n";
}
