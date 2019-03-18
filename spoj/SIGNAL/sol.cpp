#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define int long long
typedef long double ld;
typedef pair<ld,ld> point;
const ld PI=acos(-1);
ld angle(point A){
	ld x=atan2(A.x,A.y)*180.0L/PI;
	return x;
}
bool comp(const point& A,const point& B){
	return angle(A)<angle(B);
}
bool same_half(ld alpha,ld beta){
    if(beta>=0) return (alpha>beta||alpha<beta-180.0);
    return (alpha>beta && alpha<beta+180.0);
}
int tricount(vector<ld>& A){
	sort(A.begin(),A.end());
	int n=A.size();
	int sum=n*(n-1)*(n-2)/6;
	int l=0,r=0;
	for(;l<n;l++){
		while((r+1)%n!=l && same_half(A[(r+1)%n],A[l]) ){
			r=(r+1)%n;
		}
		//cout << l << " " << r << endl;
		int m=(r-l+n)%n;
		sum-=m*(m-1)/2;
		if(l==r)r++;
	}
	return sum;
}
main(){
	freopen("input.txt","r",stdin);
	double start = clock();
	int n;cin >> n;
	vector<point> A(n);
	for(int i=0;i<n;i++){
		cin >> A[i].x >> A[i].y;
	}
	int cnt1=0,cnt2=n*(n-1)*(n-2)*(n-3)/24;
	for(int i=0;i<n;i++){
		vector<ld> C;
		for(int j=0;j<n;j++){
			if(j!=i){
				C.push_back(angle(make_pair(A[j].x-A[i].x,A[j].y-A[i].y)));
			}
		}
		int x=tricount(C);
		cnt1+=x;
		cnt2-=x;
	}
 
	cout << setprecision(6) << fixed << (ld)((1.0L*cnt1+2.0L*cnt2)/((1.0L*n*(1.0L*n-1.0L)*(1.0L*n-2.0L))/6.0L))+3.0L << endl;
	cout << "Time taken: " << (clock() - start) / CLOCKS_PER_SEC << "s" << endl;
}