#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

const int N = 4000010;

int n, a[N], l[N], r[N], f[N];
stack <int> st;
vector <int> pos[N];

int main() {
    freopen("vodoncay.inp", "r", stdin);
    freopen("vodoncay.ans", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) {
        l[i] = i; while(!st.empty() && st.top() >= i-a[i]+1) l[i] = min(l[i], l[st.top()]), st.pop();
        st.push(i);
    }
    st = stack <int> ();
    for (int i = n; i >= 1; --i) {
        r[i] = i; while(!st.empty() && st.top() <= i+a[i]-1) r[i] = max(r[i], r[st.top()]), st.pop();
        st.push(i);
        pos[r[i]].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        f[i] = 1e9;
        for (int j = l[i]; j <= i; ++j) f[i] = min(f[i], f[j-1] + 1);
        for (int j = 0; j < pos[i].size(); ++j) f[i] = min(f[i], f[pos[i][j]-1] + 1);
        //cerr << i << ' ' << f[i] << endl;
    }
    int i = n;
    vector <int> ans;
    while(i > 0) {
        bool found = 0;
        for (int j = l[i]; j <= i; ++j) if (f[i] == f[j-1] + 1) { found = 1; ans.push_back(-i); i = j-1; break; }
        if (!found) for (int j = 0; j < pos[i].size(); ++j) if (f[i] == f[pos[i][j]-1] + 1) { found = 1; ans.push_back(pos[i][j]); i = pos[i][j]-1; break; }
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++i) printf("%d ", ans[i]); printf("\n");
}
/*
10
1 2 3 1 2 2 1 1 2 1
*/
