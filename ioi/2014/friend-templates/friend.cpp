#include "friend.h"
#include <bits/stdc++.h>
using namespace std;

// Find out best sample
int findSample(int n, int a[], int host[], int protocol[]) {
	int best[2] = {0, 0};
	vector <int> color(n);

	best[0] += a[0];
	for (int i = 1; i < n; ++i) {
		if (protocol[i] == 0) { // IAmYourFriend
			color[i] = color[host[i]] ^ 1;
			best[color[i]] += a[i];
		} else if (protocol[i] == 1) { // MyFriendsAreYourFriends
			color[i] = color[host[i]];
			best[color[i]] += a[i];
		} else { // WeAreYourFriends
			
		}
	}
}
