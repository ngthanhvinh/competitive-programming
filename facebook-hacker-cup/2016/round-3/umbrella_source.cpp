#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

typedef long long ll;

#define T (1<<17)

ll S;
int N,X;
ll x[100010],y[100010];
int dp[2*T],dp2[T];
map <ll, int> mp;
vector <pair <pair <ll, ll>, int> > v; // y, x, id

int a[100010];

void update_dp(int pos, int val){
	int id = T + pos;
	while(id > 0){
		dp[id] = max(dp[id], val);
		id /= 2;
	}
}

int get_dp(int L, int R, int id = 1, int low = 0, int high = T){
	if(L >= high || R <= low) return 0;
	if(L <= low && R >= high) return dp[id];
	int mid = (low + high) / 2;
	return max(get_dp(L, R, 2*id, low, mid), get_dp(L, R, 2*id+1, mid, high));
}

void func2(void){
	int i;
	
	// compress x
	mp.clear();
	REP(i,N) mp[x[i]] = 0;
	X = 0;
	snuke(mp,itr){
		(itr->second) = X;
		X++;
	}
	REP(i,N) x[i] = mp[x[i]];
	
	REP(i,2*T) dp[i] = 0;
	REP(i,T) dp2[i] = 0;
	
	v.clear();
	REP(i,N) v.push_back(make_pair(make_pair(y[i], x[i]), i));
	sort(v.begin(),v.end());
	reverse(v.begin(),v.end());
	
	int run = 0;
	REP(i,v.size()){
		if(i > 0 && v[i].first.first != v[i-1].first.first) run = 0;
		run++;
		int id = v[i].second;
		int pos = v[i].first.second;
		
		a[id] = max(dp2[pos], get_dp(pos, X)) + 1;
		
	//	cout << "A" << pos << ' ' << id << ' ' << a[id] << endl;
		
		dp2[pos] = max(dp2[pos], a[id]);
		update_dp(pos, run);
	}
	
//	REP(i,N) cout << x[i] << ' ' << y[i] << ' ' << a[i] << endl;
//	cout << endl;
}

int xx[100010];
ll t[100010];
int score[100010][2];

int func(void){
	int i;
	
	REP(i,N) x[i] = xx[i];
	REP(i,N) y[i] = t[i] * S - x[i];
	func2();
	REP(i,N) score[i][0] = a[i];
	
	REP(i,N) x[i] = xx[i];
	REP(i,N) y[i] = -t[i] * S - x[i];
	func2();
	REP(i,N) score[i][1] = a[i];
	
	int ans = 0;
	REP(i,N) ans = max(ans, score[i][0] + score[i][1] - 1);
	
	return ans;
}

void main2(void){
	int i;
	
	cin >> N >> S;
	REP(i,N) cin >> xx[i] >> t[i];
	
	int ans = func();
	
	REP(i,N) xx[i] = -xx[i];
	int ans2 = func();
	
	cout << max(ans, ans2) << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void pre(void){
}

int main(void){
	pre();
	int TC,t;
	cin >> TC;
	REP(t,TC){
		printf("Case #%d: ", t+1);
		main2();
	}
	return 0;
}
