#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("atlarge.in", "w", stdout);
	srand(time(NULL));
	cout<<70000<<endl;
	for(int i=2;i<70000;i+=3){
		cout<<i<<' '<<1<<endl;

		cout<<i<<' '<<i+1<<endl;

		cout<<i<<' '<<i+2<<endl;
	}
}