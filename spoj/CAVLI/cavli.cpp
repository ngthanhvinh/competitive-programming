#include <iostream>
#include <cstdio>
using namespace std;

const int N = 300010;

typedef pair<int,int> ii;
#define x first
#define y second

int n, cnt;
ii a[N]; bool del[N];
int rem[N];
set <ii> sx, sy;
set <ii> :: iterator it;
vector <int> vec;
int le[N], ri[N];

void add(int x) {
    int l = 1, r = cnt;

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y, sx.insert(ii(i, a[i].x)), sy.insert(ii(i, a[i].y));
    for (int i = 1; i <= n-2; ++i) {
        char c; cin >> c;
        ii it;
        if (c == 'L') { it = (*sx.begin()); sx.erase(sx.begin()); sy.erase(ii(it.first, a[it.first].y)); }
        if (c == 'R') { it = (*sx.rbegin()); sx.erase(sx.rbegin()); sy.erase(ii(it.first, a[it.first].y)); }
        if (c == 'D') { it = (*sy.begin()); sy.erase(sy.begin()); sx.erase(ii(it.first, a[it.first].x)); }
        if (c == 'U') { it = (*sy.rbegin()); sy.erase(sy.rbegin()); sx.erase(ii(it.first, a[it.first].x)); }
        vec.push_back(it.first); del[it.first] = 1;
    }
    for (int i = 0; i < n; ++i) if (!del[i]) rem[++cnt] = i;
    le[rem[1]] = rem[3]; ri[rem[1]] = rem[2];
    le[rem[2]] = rem[1]; ri[rem[2]] = rem[3];
    le[rem[3]] = rem[2]; ri[rem[3]] = rem[1];
}
