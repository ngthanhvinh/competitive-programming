#include "rail.h"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5005; 
const int inf = 1e9; 

int dis[maxn][maxn];

void findLocation(int n, int first, int location[], int stype[]) {
	auto set_type = [&](int id, int pos, int type) {
		//cerr << "set " << id << ' ' << pos << ' ' << type << endl;
		assert(pos >= 0 && pos <= 1000000);
		location[id] = pos;
		stype[id] = type;
	};

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			dis[i][j] = (i == j) ? 0 : -1;
		}
	}

	int d, mn = inf;
	set_type(0, first, 1);
	for (int i = 1; i < n; ++i) {
		dis[0][i] = getDistance(0, i);
		if (dis[0][i] < mn) {
			mn = dis[0][i], d = i; // d is of type D, which is nearest to station 0
		}
	}
	dis[d][0] = dis[0][d];
	set_type(d, dis[0][d] + first, 2);

	for (int i = 1; i < n; ++i) if (i != d) {
		dis[d][i] = getDistance(d, i);
	}

	// SOLVE
	vector < pair<int,int> > lef, rig;
	for (int i = 0; i < n; ++i) {
		if (i != d) {
			if (i == 0 || dis[0][i] == dis[0][d] + dis[d][i]) {
				lef.push_back({dis[d][i], i});
			} else {
				rig.push_back({dis[0][i], i});
			}
		}
	}
	sort(lef.begin(), lef.end());
	sort(rig.begin(), rig.end());

	// printf("lef\n");
	// for (auto &p : lef) printf("%d %d\n", p.first, p.second);
	// printf("rig\n");
	// for (auto &p : rig) printf("%d %d\n", p.first, p.second);

	/* SOLVE LEFT SIDE */
	set < pair<int,int> > down;
	for (auto &p : lef) {
		// whether this station is of type C or type D?
		// D?
		bool ok = false;
		if (!down.empty()) {
			auto lastC = (*down.begin());
			dis[p.second][lastC.second] = getDistance(p.second, lastC.second);
			int plocation = lastC.first + dis[p.second][lastC.second];

			if (plocation < location[d]) {
				// find the nearest C
				set < pair<int,int> >::iterator it = down.lower_bound({plocation, 0});
				if (it != down.begin()) {
					--it;
					auto nearestC = (*it);
					if (plocation - nearestC.first + dis[d][nearestC.second] == p.first) {
						// check shortest path from d
						ok = true;
						set_type(p.second, plocation, 2); // type D
					}
				}
			}
		}
		// C?
		if (!ok) {
			set_type(p.second, location[d] - p.first, 1);
			down.insert({location[d] - p.first, p.second});
		}
	}

	/* SOLVE RIGHT SIDE */
	set < pair<int,int> > up;
	for (auto &p : rig) {
		// whether this station is of type C or type D?
		// C?
		bool ok = false;
		if (!up.empty()) {
			auto lastD = (*up.rbegin());
			dis[p.second][lastD.second] = getDistance(p.second, lastD.second);
			int plocation = lastD.first - dis[p.second][lastD.second];

			if (plocation > location[d]) {
				// find the nearest D
				set < pair<int,int> >::iterator it = up.upper_bound({plocation, inf});
				if (it != up.end()) {
					auto nearestD = (*it);
					if (nearestD.first - plocation + dis[0][nearestD.second] == p.first) {
						// check shortest path from 0
						ok = true;
						set_type(p.second, plocation, 1); // type C
					}
				}
			}
		}
		// D?
		if (!ok) {
			set_type(p.second, location[0] + p.first, 2);
			up.insert({location[0] + p.first, p.second});
		}
	}
}
