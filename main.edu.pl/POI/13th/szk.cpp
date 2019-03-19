#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define N 405
#define int long long

class Hungarian {
#define arg __arg
	long long c[N][N];
	long long fx[N], fy[N];
	int mx[N], my[N];
	int trace[N], qu[N], arg[N];
	long long d[N];
	int front, rear, start, finish;
	int n;
	const int inf = 1e9;
public:
	void init(int _n) {
		n = _n;
		for (int i = 1; i <= n; i++) {
			fy[i] = mx[i] = my[i] = 0;
			for (int j = 1; j <= n; j++) c[i][j] = inf;
		}
	}

	void addEdge(int i, int j, long long cost) {
		c[i][j] = min(c[i][j], cost);
	}
private:
	inline long long getC(int i, int j) {
		return c[i][j] - fx[i] - fy[j];
	}

	void initBFS() {
		front = rear = 1;
		qu[1] = start;
		memset(trace, 0, sizeof trace);
		for (int j = 1; j <= n; j++) {
			d[j] = getC(start, j);
			arg[j] = start;
		}
		finish = 0;
	}

	void findAugPath() {
		while (front <= rear) {
			int i = qu[front++];
			for (int j = 1; j <= n; j++) if (!trace[j]) {
					long long w = getC(i, j);
					if (!w) {
						trace[j] = i;
						if (!my[j]) {
							finish = j;
							return ;
						}
						qu[++rear] = my[j];
					}
					if (d[j] > w) {
						d[j] = w;
						arg[j] = i;
					}
				}
		}
	}

	void subx_addy() {
		long long delta = inf;
		for (int j = 1; j <= n; j++)
			if (trace[j] == 0 && d[j] < delta) delta = d[j];

		// xoay
		fx[start] += delta;
		for (int j = 1; j <= n; j++)
			if (trace[j]) {
				int i = my[j];
				fy[j] -= delta;
				fx[i] += delta;
			}
			else d[j] -= delta;

		for (int j = 1; j <= n; j++)
			if (!trace[j] && !d[j]) {
				trace[j] = arg[j];
				if (!my[j]) { finish = j; return ; }
				qu[++rear] = my[j];
			}
	}

	void enlarge() {
		do {
			int i = trace[finish];
			int next = mx[i];
			mx[i] = finish;
			my[finish] = i;
			finish = next;
		} while (finish);
	}
public:
	pair<int, int> mincost() {
		for (int i = 1; i <= n; i++) fx[i] = *min_element(c[i] + 1, c[i] + n + 1);
		for (int j = 1; j <= n; j++) {
			fy[j] = c[1][j] - fx[1];
			for (int i = 1; i <= n; i++) {
				fy[j] = min(fy[j], c[i][j] - fx[i]);
			}
		}
		for (int i = 1; i <= n; i++) {
			start = i;
			initBFS();
			while (finish == 0) {
				findAugPath();
				if (!finish) subx_addy();
			}
			enlarge();
		}
		pair<int, int> res = make_pair(0, 0);
		for (int i = 1; i <= n; i++) {
			if (c[i][mx[i]] == inf) continue;
			res.fi += c[i][mx[i]];
			res.se++;
		}
		return res;
	}
} MCMF;

int n;
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
// #ifdef UncleGrandpa
// 	freopen("1test.inp", "r", stdin);
// #endif
	cin >> n;
	MCMF.init(2 * n);
	for (int i = 1; i <= n; i++) {
		int m, l, r, c;
		cin >> m >> l >> r >> c;
		for (int j = l; j <= r; j++) {
			MCMF.addEdge(i, n + j, c * abs(m - j));
		}
	}
	pair<int, int> rec = MCMF.mincost();
	if (rec.se != n) {
		cout << "NIE" << endl;
	}
	else cout << rec.fi << endl;
}