#include <bits/stdc++.h>
#include "testlib.h"

#define pb push_back
#define ll long long
#define mp make_pair
#define f first
#define s second
#define pii pair < int, int >
#define ull unsigned long long
#define pll pair < ll, ll >
#define forit(it, s) for(__typeof(s.begin()) it = s.begin(); it != s.end(); it ++)
#define all(s) s.begin(), s.end()

const int maxn = (int) 1e5 + 10;

using namespace std;

vector < pii > ed;
int a[1000100];
int p[1000200];
int pos[1000200];

int getrand(int l, int r){
	return rnd.next(l, r);
}
void cons(int n){
	for(int i = 0; i < n; i++){
		pos[i] = i;
	}
	for(int i = 1; i < n; i++){
		swap(pos[i], pos[getrand(0, i-1)]);
	}
	printf("%d\n", n);
	int la = 0, sz = 0, cur = n/2;
	for(int i = 1; i < n; i++){
		sz++;
		if(sz > cur){
			printf("%d %d\n", pos[la]+1, pos[i] + 1);
			la = i;
			sz = 0;
			cur = (n - i - 1)/2;
		}else {
			printf("%d %d\n", pos[i-1]+1, pos[i] + 1);
		}
	}
	
}


int main (int argc, char* argv[]) {
    
    registerGen(argc, argv, 1);
    
    int n = atoi(argv[1]);
    cons(n);
    return 0;
}


