// http://wcipeg.com/problem/noi11p6
// Day 2, Problem 3 - Bunny and Eggy's Game

#include <bits/stdc++.h>
using namespace std;

const int N = 45;
const int dx[] = {0, 0, -1, +1}, dy[] = {-1, +1, 0, 0};

int n, m, nturn;
int nmatch;
char a[N][N];
vector<int> G[N * N];
int match[N * N];
bool check[N * N], del[N * N];
vector<int> buf;
int pos;
vector<int> bunny;

int id(int x, int y) { return x * m + y; }

bool dfs(int u, bool flag) {
    if (u == -1) return true;
    check[u] = true;
    buf.push_back(u);
    for (int v : G[u]) {
        if (!check[v] && !del[v]) {
            check[v] = true;
            buf.push_back(v);
            if (dfs(match[v], flag)) {
                if (flag) { match[u] = v; match[v] = u; }
                return true;
            }
        }
    }
    return false;
}

void reset() {
    while(buf.size()) check[buf.back()] = false, buf.pop_back();
}

void move(int x, int y) { // {pos} is current position of the blank cell
    reset();
    del[pos] = true;
    if (match[pos] != -1) {
        match[match[pos]] = -1;
        if (!dfs(match[pos], 1)) --nmatch;
    }
    match[pos] = -1;

    pos = id(x - 1, y - 1); // (x, y) is the new position
}

bool win() {
    reset();
    // check whether {pos} is included in every max matching
    if (match[pos] == -1) return false;
    check[pos] = true;
    buf.push_back(pos);
    if (dfs(match[pos], 0)) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            if (a[i][j] == '.') pos = id(i, j);
        }
    }

    // build edges
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int dir = 0; dir < 4; ++dir) {
                int ni = i + dx[dir], nj = j + dy[dir];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                if (a[i][j] == a[ni][nj]) continue;
                if ((a[i][j] == '.' && a[ni][nj] == 'X') || (a[i][j] == 'X' && a[ni][nj] == '.')) continue;
                G[id(i, j)].push_back(id(ni, nj));
            }
        }
    }

    // bipartite matching
    memset(match, -1, sizeof match);
    int rem = n * m, prev_rem = n * m + 1;
    while(rem > 0 && rem < prev_rem) {
        prev_rem = rem;
        reset();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int c = id(i, j);
                if (a[i][j] == 'O' && match[c] == -1) rem -= dfs(c, 1);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int c = id(i, j);
            if (a[i][j] == 'O') nmatch += match[c] != -1;
        }
    }

    // solve queries
    cin >> nturn;
    bool cur = win();
    bool nxt;
    for (int i = 1; i <= nturn; ++i) {
        int bx, by; cin >> bx >> by; // Bunny
        move(bx, by);
        nxt = win(); // nxt = 1 -> Eggy wins
        if (cur && nxt) bunny.push_back(i);

        int ex, ey; cin >> ex >> ey; // Eggy
        move(ex, ey);
        cur = win();
    }

    cout << bunny.size() << endl;
    for (int &i : bunny) cout << i << endl;
}