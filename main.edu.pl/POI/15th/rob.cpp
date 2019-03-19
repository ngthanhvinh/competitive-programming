#include <bits/stdc++.h>
using namespace std;

const int N = 6020;
int n;
int _n;
char a[N][N], tmp[N][N];
int centerx, centery;
vector<int> v[2];

bool symmetryX() {
    v[0].clear(); v[1].clear();
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        for (int j = 1; j <= n; ++j) {
            if (a[i][j] == 'r') ++cnt; else cnt = 0;
            mx = max(mx, cnt);
        }
    }
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        int lst = 0;
        for (int j = 1; j <= n; ++j) {
            if (a[i][j] == 'r') ++cnt; else lst = j, cnt = 0;
            if (cnt == mx) {
                centerx = i; centery = lst + (j - lst + 1) / 2; break;
            }
        }
    }

    for (int i = centerx; i >= 1; --i) {
        if (a[i][centery] != 'r') break;
        int j = 0;
        while(centery - j >= 1 && centery + j <= n) {
            if (a[i][centery-j] == 'r' && a[i][centery+j] != 'r') return false;
            if (a[i][centery-j] != 'r' && a[i][centery+j] == 'r') return false;
            if (a[i][centery-j] == 'r' && a[i][centery+j] == 'r') ++j; else break;
        }
        --j;
        v[0].push_back(j + 1);
    }
    for (int i = centerx; i <= n; ++i) {
        if (a[i][centery] != 'r') break;
        int j = 0;
        while(centery - j >= 1 && centery + j <= n) {
            if (a[i][centery-j] == 'r' && a[i][centery+j] != 'r') return false;
            if (a[i][centery-j] != 'r' && a[i][centery+j] == 'r') return false;
            if (a[i][centery-j] == 'r' && a[i][centery+j] == 'r') ++j; else break;
        }
        --j;
        v[1].push_back(j + 1);
    }
    reverse(v[0].begin(), v[0].end());
    reverse(v[1].begin(), v[1].end());
    return true;
}

void rotate_90() {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) tmp[j][n - i + 1] = a[i][j];
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) a[i][j] = tmp[i][j];
}
void rotate_180() {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) tmp[n+1-i][n+1-j] = a[i][j];
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) a[i][j] = tmp[i][j];
}
void multiply() {
    for (int i = 1; i <= n * 3; ++i) for (int j = 1; j <= n * 3; ++j) tmp[i][j] = '.';
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) tmp[i+n][j+n] = a[i][j];
    _n = n; n *= 3;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) a[i][j] = tmp[i][j];
}

int nearest[N], l[N], r[N];
int f[N][N];
bool check[N][N];

void solve(int id) {
    int ptr = 0;
    for (int val = 1; val <= n; ++val) {
        while(ptr < v[id].size() && v[id][ptr] <= val) ++ptr;
        nearest[val] = ptr;
    }
    for (int i = 1; i <= n; ++i) {
        l[0] = 0; for (int j = 1; j <= n; ++j) { if (a[i][j] == 'X') l[j] = j; else l[j] = l[j-1]; }
        r[n+1] = n+1; for (int j = n; j >= 1; --j) { if (a[i][j] == 'X') r[j] = j; else r[j] = r[j+1]; }
        for (int j = 1; j <= n; ++j) f[i][j] = nearest[min(j - l[j], r[j] - j)];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (f[i][j] > f[i-1][j]) f[i][j] = f[i-1][j] + 1;
        }
    }
}

bool in(int x, int y) { return (x >= _n + 1 && x <= _n + _n && y >= _n + 1 && y <= _n + _n); }

bool out(int x, int y) {
    if (in(x,y)) return false;
    if (x >= _n + 1 && x <= _n + _n) {
        if (in(x, y - v[0].back() + 1)) return false;
        if (in(x, y + v[0].back() - 1)) return false;
    } else if (x <= _n) {
        int h = _n + 1 - x;
        h = v[1].size() - 1 - h;
        if (h >= 0) {
            if (in(_n + 1, y - v[1][h] + 1)) return false;
            if (in(_n + 1, y + v[1][h] - 1)) return false;
        }
    } else {
        int h = x - (_n + _n);
        h = v[0].size() - 1 - h;
        if (h >= 0) {
            if (in(_n + _n, y - v[0][h] + 1)) return false;
            if (in(_n + _n, y + v[0][h] - 1)) return false;
        }
    }
    return true;
}

const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};
int bfs() {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) f[i][j] = N * N;
    queue < pair<int,int> > q;
    q.push(make_pair(centerx, centery)); f[centerx][centery] = 0;
    while(!q.empty()) {
        int x = q.front().first, y = q.front().second; q.pop();
        if (out(x, y)) return f[x][y];
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (nx <= 0 || nx > n || ny <= 0 || ny > n || !check[nx][ny]) continue;
            f[nx][ny] = f[x][y] + 1;
            q.push(make_pair(nx, ny));
            check[nx][ny] = 0;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        for (int j = 1; j <= n; ++j) a[i][j] = s[j-1];
    }
    if (!symmetryX()) rotate_90();
    symmetryX();
    multiply();
    centerx += _n; centery += _n;

    solve(0);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (f[i][j] == v[0].size()) check[i][j] = 1;

    rotate_180();
    solve(1);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (f[n+1-i][n+1-j] != v[1].size()) check[i][j] = 0;
    rotate_180();

    // BFS
    int res = bfs();
    if (res == -1) cout << "NIE\n"; else cout << res << '\n';
}