#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int N = 100010;
typedef pair<int,int> ii;
typedef pair<ii, int> II;

int n;
ii a[N];
vector <II> v;
set <ii> s;
vector <int> w[N];
int pos[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].second >> a[i].first, a[i].second += a[i].first, swap(a[i].first, a[i].second), v.push_back(II(a[i], i));
    sort(v.begin(), v.end());
    int cnt = 0;
    for (int i = 0; i < v.size(); ++i) {
        int l = v[i].first.second, r = v[i].first.first;
        //cerr << l << ' ' << r << endl;
        set<ii>::iterator it = s.upper_bound(ii(l + 1, 0));
        if (it == s.begin()) {
            ++cnt; w[cnt].push_back(v[i].second);
            s.insert(ii(r, n-cnt));
        }
        else {
            --it; ii cur = (*it); w[n-cur.second].push_back(v[i].second);
            s.erase(it);
            s.insert(ii(r, cur.second));
        }
    }

    int num = 0;
    for (int i = 1; i <= cnt; ++i) {
        for (int j = 0; j < w[i].size(); ++j) pos[++num] = w[i][j];
        //cerr << endl;
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= n; ++i) printf("%d\n", pos[i]);
}
