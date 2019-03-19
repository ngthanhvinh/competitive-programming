#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int sz;
    vector<int> T;
	vector<int> lz;
    SegmentTree() {}
    void init(int SIZE = 0) {
        sz = SIZE; T.assign(4 * sz + 10, 0); lz.assign(4 * sz + 10, 0);
    }
    #define mid ((l + r) >> 1)
	void push(int v, int l, int r) {
		if (!lz[v]) return;
		if (l < r) lz[v << 1] = lz[v], lz[v << 1 | 1] = lz[v];
		T[v] = lz[v]; lz[v] = 0;
	}
    void upd(int v, int l, int r, int L, int R, int val) {
		push(v, l, r);
        if (l > r || R < l || L > r) return;
        if (L <= l && r <= R) { lz[v] = val; push(v, l, r); return; }
        upd(v << 1, l, mid, L, R, val); upd(v << 1 | 1, mid + 1, r, L, R, val);
        T[v] = max(T[v << 1], T[v << 1 | 1]);
    }
    int get(int v, int l, int r, int L, int R) {
		push(v, l, r);
        if (l > r || R < l || L > r) return 0;
        if (L <= l && r <= R) return T[v];
        return max(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
    }
    void upd(int l, int r, int val) { upd(1, 0, sz, l, r, val); }
    int get(int l, int r) { return get(1, 0, sz, l, r); }
    #undef mid
};

struct SegmentTree2D {
    int nr, nc;
    vector<SegmentTree> tree;
    void init(int _nr = 0, int _nc = 0) {
        nr = _nr; nc = _nc;
        tree.assign(4 * nr + 10, SegmentTree());
        for (int i = 0; i < tree.size(); ++i) {
            tree[i].init(nc);
        }
    }

    void merge(int vx, int lx, int rx, int vy, int ly, int ry, int y1, int y2) {
        if (ly > ry || y2 < ly || y1 > ry) return;
        if (y1 <= ly && ry <= y2) {
            if (lx < rx) tree[vx << 1].lz[vy] = tree[vx].lz[vy], tree[vx << 1 | 1].lz[vy] = tree[vx].lz[vy];
            tree[vx].push(vy, ly, ry); 
            return;
        }
        merge(vx, lx, rx, vy << 1, ly, ((ly + ry) >> 1), y1, y2);
        merge(vx, lx, rx, vy << 1 | 1, ((ly + ry) >> 1) + 1, ry, y1, y2);
        tree[vx].T[vy] = max(tree[vx].T[vy << 1], tree[vx].T[vy << 1 | 1]);
    }

    void push(int vx, int lx, int rx, int vy, int ly, int ry, int y1, int y2) {
        if (ly > ry || y2 < ly || y1 > ry) return;
        if (y1 <= ly && ry <= y2) {
            //cerr << "push " << lx << ' ' << rx << ' ' << ly << ' ' << ry << ' ' << tree[vx].lz[vy] << endl;
            if (lx < rx) tree[vx << 1].lz[vy] = tree[vx].lz[vy], tree[vx << 1 | 1].lz[vy] = tree[vx].lz[vy];
            tree[vx].push(vy, ly, ry);
            return;
        }
        push(vx, lx, rx, vy << 1, ly, ((ly + ry) >> 1), y1, y2);
        push(vx, lx, ry, vy << 1 | 1, ((ly + ry) >> 1) + 1, ry, y1, y2);
    }

    #define mid ((l + r) >> 1)
    void upd(int v, int l, int r, int lx, int rx, int ly, int ry, int val) {
        merge(v, l, r, 1, 0, nc, ly, ry);
        if (l > r || rx < l || lx > r) return;
        if (lx <= l && r <= rx) {
            tree[v].upd(ly, ry, val); return;
        }
        upd(v << 1, l, mid, lx, rx, ly, ry, val);
		upd(v << 1 | 1, mid + 1, r, lx, rx, ly, ry, val);
        merge(v, l, r, 1, 0, nc, ly, ry);
    }

    int get(int v, int l, int r, int lx, int rx, int ly, int ry) {
        merge(v, l, r, 1, 0, nc, ly, ry);
        if (l > r || rx < l || lx > r) return 0;
        if (lx <= l && r <= rx) return tree[v].get(ly, ry);
        return max(get(v << 1, l, mid, lx, rx, ly, ry), get(v << 1 | 1, mid + 1, r, lx, rx, ly, ry));
    }
    #undef mid

    void upd(int lx, int rx, int ly, int ry, int val) { return upd(1, 0, nr, lx, rx, ly, ry, val); }
    int get(int lx, int rx, int ly, int ry) { return get(1, 0, nr, lx, rx, ly, ry); }
} seg2d;

int D, S, n;

int main() {
	cin >> D >> S >> n;
	seg2d.init(D, S);
	while(n--) {
		int d, s, w, x, y;
		cin >> d >> s >> w >> x >> y;
		int mx = seg2d.get(x, x + d, y, y + s);
		cerr << mx << endl;
		mx += w;
		seg2d.upd(x, x + d, y, y + s, mx);
		cerr << x << ' ' << x + d << ' ' << y << ' ' << y + s << ' ' << mx << endl;
		cerr << "debug\n";
		for (int i = 0; i <= D; ++i) {
			for (int j = 0; j <= S; ++j) cerr << "get " << i << ' ' << j << endl << seg2d.get(i, i, j, j) << endl;
			cerr << endl;
		}
	}
	cout << seg2d.get(0, D, 0, S) << endl;
}