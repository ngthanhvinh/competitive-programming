#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for(int i = a, _b = b; i <= _b; ++ i)
#define REP(i, a) for(int i = 0, _a = a; i < _a; ++ i)
#define FORD(i, a, b) for(int i = a, _b = b; i >= _b; -- i)
#define llint long long
#define sz(a) (int(a.size()))
#define RESET(a, v) memset(a, (v), sizeof(a))
#define fi first
#define se second
#define mp make_pair
#define LL(x) (x << 1)
#define RR(x) ((x << 1) + 1)
#define endl '\n'
#define db(x) cout << #x << " = " << x << endl;
#define in cout <<
#define _ << " " <<
#define out << endl

void Openfile(){
    freopen("message1.inp", "r", stdin);
    freopen("message1.out", "w", stdout);
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
}

const int maxN = 1e2 + 5;
const int maxM = 1e6 + 5;
const llint INF = 1e9 + 7;

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

inline char nextCharacter(){
	register char c = getchar();
	while (c < 'a' || c > 'z') c = getchar();
	return c;
}

void writeInt(llint x){
	if (x < 0){
		putchar('-');
		x = -x;
	}
	if (x >= 10) writeInt(x / 10);
	putchar(x % 10 + 48);
}

int N, M, T;
int a[maxN][maxN], b[maxN][maxN];
llint Ha[maxN][maxN], Hb[maxN][maxN];
llint Pow[maxN * maxN];
unordered_map<llint, bool> HashMap;

void Init(){
	Pow[0] = 1;
	FOR(i, 1, maxN * maxN - 1){
		Pow[i] = Pow[i - 1] * 27;
	}
}

void Enter(){
	N = nextInt(); M = nextInt();
	FOR(i, 1, N){
		FOR(j, 1, M){
			a[i][j] = nextCharacter() - 'a' + 1;
		}
	}
	FOR(i, 1, N){
		FOR(j, 1, M){
			b[i][j] = nextCharacter() - 'a' + 1;
		}
	}
}

llint Hash(llint H[maxN][maxN], int x[maxN][maxN]){
	FOR(i, 1, N)
	FOR(j, 1, M)
		H[i][j] = x[i][j]
			+ H[i][j - 1] * Pow[1]
			+ H[i - 1][j] * Pow[M]
			- H[i - 1][j - 1] * Pow[M + 1];
}

llint GetHash(llint H[maxN][maxN], int x, int y, int u, int v){
	--x; --y;
	return H[u][v]
	- H[u][y] * Pow[v - y]
	- H[x][v] * Pow[(u - x) * M]
	+ H[x][y] * Pow[(u - x) * M + v - y];
}

bool FoundRectangle(int x, int y){
	HashMap.clear();
	FOR(i, x, N){
		FOR(j, y, M){
			HashMap[GetHash(Ha, i - x + 1, j - y + 1, i, j)] = true;
		}
	}

	FOR(i, x, N){
		FOR(j, y, M){
			if (HashMap[GetHash(Hb, i - x + 1, j - y + 1, i, j)]){
				return true;
			}
		}
	}

	return false;
}

void Solve(){
	Hash(Ha, a);
	Hash(Hb, b);

	int j = M, ans = 0;

	FOR(i, 1, N){
		while (!FoundRectangle(i, j)) --j;
		ans = max(ans, i * j);
	}

	writeInt(ans);
	putchar('\n');
}

int main(){
	Openfile();
	T = nextInt();
	while (T --){
		Init();
		Enter();
		Solve();
	}
	return 0;
}
