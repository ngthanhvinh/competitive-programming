#include <bits/stdc++.h>
using namespace std;
int test,n,a[107],dp[107][8007];
int main(){
	ios_base::sync_with_stdio(0);
	cin>>test;
	for(int t=1;t<=test;t++){
		cin>>n;
		int ans=1;
		for(int i=1;i<=n;i++) cin>>a[i];
		memset(dp,-1,sizeof(dp));
		for(int i=0;i<=n;i++) dp[i][0]=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=6*a[i];j++){
				//cout<<dp[i][j]<<" ";
				if(dp[i-1][j]==-1) continue;
				dp[i][j+a[i]]=max(dp[i][j+a[i]],dp[i-1][j]+1);
			}
			for(int j=0;j<=8000;j++) dp[i][j]=max(dp[i-1][j],dp[i][j]), ans=max(ans,dp[i][j]);
		}
		cout<<"Case #"<<t<<": "<<ans<<"\n";
	}
}
