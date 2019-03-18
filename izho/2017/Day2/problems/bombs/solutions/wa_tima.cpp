#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <cstring>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <bitset>
#define f first
#define s second
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb push_back
#define vi vector <int>
#define ld long double
#define pii pair<int, int>
#define y1 sda
using namespace std;    
const int N = 2510, mod = int(1e9)  + 7; 

int n,m;
char s[N][N];
int d[N][N], dp[N][N];

int main () {
	freopen("bomb.in","r", stdin);
	freopen("bomb.out","w", stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++){
		scanf("\n%s",s[i] + 1);
		for(int j = 1; j <= m; j++){
			if(s[i][j] == '0'){
				d[i][j] = 0;
				dp[i][j] = 0;
			}	
			else{
				d[i][j] = d[i][j - 1] + 1;
				dp[i][j] = dp[i - 1][j] + 1;
			}
		}
	}
	int x = -1, y = -1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(s[i][j] == '0') continue;
			if(j == m || s[i][j + 1] == '0'){
				if(x == -1) x = d[i][j];
				else x = min(x, d[i][j]);
			}
			if(i == n || s[i + 1][j] == '0'){
				if(y == -1) y = dp[i][j];
				else y = min(y, dp[i][j]);
			}
		}
	}
	cout << x * y;



return 0;
}