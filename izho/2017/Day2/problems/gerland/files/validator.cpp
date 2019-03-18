#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

map <int, int> was;
int a[int(2e6)];

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();
    for (int i = 1; i <= n; i++) {
        int x = inf.readInt(1, int(1e6), "init");
        was[x]++;
        a[i] = x;
        if (i < n) inf.readSpace();
    }
    inf.readEoln();
    for(int i = 0; i < m; ++i) {
        int T = inf.readInt(1, 2, "Query type");
        inf.readSpace();
        if (T == 1) {
          int v = inf.readInt(1, n, "position");
          inf.readSpace();
          int x = inf.readInt(1, int(1e6), "value");
          was[a[v]]--;
          a[v] = x;
          was[a[v]]++;
        }
        if (T == 2) {
            int x = inf.readInt(1, int(1e6), "query_value");
            assert(!was[x]);
        }
        inf.readEoln();
    }
    inf.readEof();
}

