#include <bits/stdc++.h>

#define FOR(i, a, b) for(int i = a, _b = b; i <= _b; i ++)
#define REP(i, a, b) for(int i = a, _b = b; i < _b; i ++)
#define FORD(i, a, b) for(int i = a, _b = b; i >= _b; i --)
#define llint long long
#define sz(a) (int(a.size()))
#define RESET(a, v) memset(a, (v), sizeof(a))
#define X first
#define Y second
#define mp make_pair
#define LL(x) (x << 1)
#define RR(x) ((x << 1) + 1)
#define endl '\n'
#define db(x) cout << #x << " = " << x << endl;

const int maxN = 1e5 + 5;
const int maxM = 1e6 + 5;
const llint INF = 1e9 + 7;

using namespace std;

inline llint nextInt(){
	register char c = getchar();
	bool neg = false;
	llint ret = 0;
	while (c < '0' || c > '9'){
		if (c == '-') neg = true;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		ret = (ret << 1) + (ret << 3) + c - '0';
		c = getchar();
	}
	if (neg) ret = -ret;
	return ret;
}

void writeInt(llint x){
	if (x < 0){
		putchar('-');
		x = -x;
	}
	if (x >= 10) writeInt(x / 10);
	putchar(x % 10 + 48);
}
int K;
int a[64];
llint b[5][64], d[64];

void Openfile(){
	std :: ios_base ::sync_with_stdio(false);
	cin.tie(0);
	#ifdef ZEUSTRONG
	freopen("bonus13.inp", "r", stdin);
	freopen("bonus13.out", "w",  stdout);
	#endif
}

void Init(){

}

inline int H(int x, int y){return x * 8 + y;}

void Enter(){
	K = nextInt();
	FOR(i, 1, K){
		int u, v, c;
		u = nextInt(); v = nextInt(); c = nextInt();
		a[H(u - 1, v - 1)] = c;
	}
}

int sl, slh;

inline llint check(llint x){
	llint ret = 0;
	REP(i, 0, sl){
		if ((x >> i) & 1ll){
			ret = ret + d[i];
		}
	}
	return ret;
}

llint ans = 0;

void Solve(){
	sl = slh = 0;
	REP(i, 0, 8){
		REP(j, 0, 8){
			if (a[H(i, j)] != 0){
				d[sl++] = a[H(i, j)];
			}
		}
	}

	int x = 0, y = 0;
	REP(i, 0, 8){
		REP(j, 0, 8){
			if (a[H(i, j)]) continue;
			int g = 0;
			REP(u, 0, 8){
				REP(v, 0, 8){
					if (a[H(u, v)] == 0) continue;
					if ((i == u) || (j == v) || (i + j == u + v) || (i - j == u - v))
						b[1][x] |= (1ll << g);

					if ((i == u) || (j == v))
						b[2][x] |= (1ll << g);

					if ((i + j == u + v) || (i - j == u - v))
						b[3][x] |= (1ll << g);

					if ((abs(i - u) == 2 && abs(j - v) == 1) || (abs(i - u) == 1 && abs(j - v) == 2))
						b[4][x] |= (1ll << g);

					++g;
				}
			}
			++x;
		}
	}

	slh = 8 * 8 - sl;

	llint cur, lastj, lastt, lastk;
	REP(i, 0, slh){
		cur = b[1][i];
		REP(j, 0, slh) if (i != j){
			lastj = cur;
			cur |= b[2][j];
			REP(t, 0, slh) if (t != i && t != j){
				lastt = cur;
				cur |= b[3][t];
				REP(k, 0, slh) if (k != i && k != j && k != t){
					lastk = cur;
					cur |= b[4][k];

					ans = max(ans, check(cur));

					cur = lastk;
				}
				cur = lastt;
			}
			cur = lastj;
		}
	}

	writeInt(ans);
}

int main(){
	Openfile();
	Init();
	Enter();
	Solve();
	return 0;
}
