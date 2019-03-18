#include <bits/stdc++.h>
#include "askonegetonefree.h"
using namespace std;

int f[10005];
int best[10005];
int lg[10005];
bool prepared = false;

int Guess(int low, int high, int side) {
	if (low == high) return low;

	int mid = ((low + high + 1) >> 1);
	Answer reply = query(mid);

	int ans;
	if (!side) ans = reply.p; else ans = reply.q;

	if (ans) { // x >= mid
		return Guess(mid, high, side);
	} else { // x < mid
		return Guess(low, mid - 1, side);
	}
}

void prep() {
	if (prepared) return;
	prepared = true;

	for (int i = 2; i <= 10000; ++i) lg[i] = lg[i >> 1] + 1;

	f[1] = 0;
	for (int i = 2; i <= 10000; ++i) {
		int mn = 1e9;
		best[i] = 1;
		for (int j = 1; j < i; ++j) {
			int cur = max({f[j], f[i - j], 1 + lg[j] + lg[i - j]});
			if (mn > cur) mn = cur, best[i] = j;
		}
	}
}

Answer guess(int N) {
  Answer reply;      // reply from Bob
  Answer secrets;    // Your guessed secrets

  //----------  Put your code below  -------------------//
  
  prep();
  reply = query(best[N]);
  if (reply.p == 1 && reply.q == 1) {
  	
  } 
  if (reply.p == 0 && reply.q == 0) {

  }
  if (reply.p == 0 && reply.q == 1) {

  }
  if (reply.p == 1 && reply.q == 0) {

  }

	return (secrets);
}
