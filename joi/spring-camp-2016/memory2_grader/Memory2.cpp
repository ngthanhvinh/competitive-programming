#include "Memory2_lib.h"
#include <bits/stdc++.h>
using namespace std;

static const int MAX = 50;
static vector<int> pos[MAX];

void Solve(int T, int N){
	srand(time(NULL));
	vector<int> rem;
	for (int i = 0; i < 2 * N; ++i) rem.push_back(i);

	while(rem.size()) {
		// reset
		for (int i = 0; i < MAX; ++i) pos[i].clear();

		// ask
		int pivot = rem[rand() % rem.size()];

		for (int p : rem) if (p != pivot) {
			int reply = Flip(p, pivot);
			pos[reply].push_back(p);
		}

		int cur;
		for (int i = 0; i < MAX; ++i) {
			if (pos[i].size() == 2) {
				Answer(min(pos[i][0], pos[i][1]), max(pos[i][0], pos[i][1]), i);
				rem.erase(find(rem.begin(), rem.end(), pos[i][0]));
				rem.erase(find(rem.begin(), rem.end(), pos[i][1]));
			} else if (pos[i].size() & 1) {
				cur = i;
			}
		}

		if (rem.size() == 2) { // only 2 cards remain
			Answer(min(rem[0], rem[1]), max(rem[0], rem[1]), cur);
			break;
		}
	}		
}
