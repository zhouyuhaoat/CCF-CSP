/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-06 16:10:42
 * 	modified: 	2024-07-07 12:23:18
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int maxn = 300010;

/*
0. quadrilateral shield = circle; altar = center
0. maximum the level and the scheme
1. altar must be the integer point
2. suppose exists (up, down, left, right)-number points in four direction
2. the level of the quadrilateral shield = min(up, down, left, right)
3. suppose exist (a <= b <= c <= d)-number points in four direction
3. the count of the scheme = C_b^a * C_c^a * C_d^a, C represents the combination
4. the relative position of the point matters, not the absolute position
4. compress: discretization process
5. Scan Line and Segment Tree
*/

struct point {
	int x, y;
} p[maxn];

struct node { // segment tree
	int l, r, v, c;
	// interval or range: [left, right]
	// v: level by max; c: scheme by sum
	node *lc, *rc;
	node(int l, int r) : l(l), r(r), v(0), c(0), lc(nullptr), rc(nullptr) {
	}
} *root;

void update(node *now) { // pushup
	now->v = max(now->lc->v, now->rc->v);
	now->c = now->lc->c + now->rc->c;
}

void build(node *&now, int l, int r) { // create
	now = new node(l, r);
	if (l == r) {
		return;
	}
	int mi = (l + r) >> 1;
	build(now->lc, l, mi);
	build(now->rc, mi + 1, r);
}

void modify(node *now, int x, int v, int c) { // single point
	if (x > now->r || x < now->l) {
		return;
	}
	if (x == now->l && x == now->r) { // leaf
		now->v = v, now->c = c;
		return;
	}
	modify(now->lc, x, v, c);
	modify(now->rc, x, v, c);
	update(now);
}

int queryLevel(node *now, int l, int r) {
	if (l > now->r || r < now->l) {
		return 0;
	}
	if (l <= now->l && r >= now->r) {
		return now->v;
	}
	return max(queryLevel(now->lc, l, r), queryLevel(now->rc, l, r));
}

int queryCount(node *now, int l, int r) {
	if (l > now->r || r < now->l) {
		return 0;
	}
	if (l <= now->l && r >= now->r) {
		return now->c;
	}
	return queryCount(now->lc, l, r) + queryCount(now->rc, l, r);
}

int totx, toty; // tot: total
map<int, int> xmap, ymap;
// axis-map: axis-coordinate after discretization
vector<point> xpoint[maxn], ypoint[maxn];
// axis-point: points with same axis-coordinate
int le[maxn], ri[maxn];
// count points in the left and right of the point in y-axis

void discrete(int n) { // discretization process
	sort(p + 1, p + n + 1, [](const point &a, const point &b) {
		if (a.x != b.x) {
			return a.x < b.x;
		}
		return a.y < b.y;
	});
	p[0].x = -1;
	for (int i = 1; i <= n; i++) {
		if (p[i].x != p[i - 1].x) {
			xmap[p[i].x] = ++totx;
		}
		xpoint[totx].emplace_back(p[i]);
	}
	sort(p + 1, p + n + 1, [](const point &a, const point &b) {
		if (a.y != b.y) {
			return a.y < b.y;
		}
		return a.x < b.x;
	});
	p[0].y = -1;
	for (int i = 1; i <= n; i++) {
		if (p[i].y != p[i - 1].y) {
			ymap[p[i].y] = ++toty;
		}
		ypoint[toty].emplace_back(p[i]);
	}
}

int main(int argc, char const *argv[]) {

	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> p[i].x >> p[i].y;
	}
	discrete(n);
	build(root, 1, toty); // toty: y-axis
	for (int i = 1; i <= toty; i++) {
		le[i] = 0;
		ri[i] = ypoint[i].size();
	}
	int ans1 = 0;
	for (int i = 1; i <= totx; i++) { // totx: x-axis
		int tot = xpoint[i].size();
		for (int j = 0; j < tot; j++) {
			int ydes = ymap[xpoint[i][j].y];
			++le[ydes], --ri[ydes];
			modify(root, ydes, min(le[ydes], ri[ydes]), 0);
		}
		for (int j = 0; j < tot - 1; j++) { // pair: interval or range
			int desy1 = ymap[xpoint[i][j].y];
			int desy2 = ymap[xpoint[i][j + 1].y];
			int res = queryLevel(root, desy1 + 1, desy2 - 1);	   // y-axis
			ans1 = max(ans1, min(res, min(j + 1, tot - (j + 1)))); // x-axis
		}
	}
	if (q == 1) {
		cout << ans1 << "\n";
	} else {
		for (int i = 1; i <= toty; i++) {
			le[i] = 0;
			ri[i] = ypoint[i].size();
		}
		int ans2 = 0;
		for (int i = 1; i <= totx; i++) {
			int tot = xpoint[i].size();
			for (int j = 0; j < tot; j++) {
				int ydes = ymap[xpoint[i][j].y];
				++le[ydes], --ri[ydes];
				modify(root, ydes, 0, min(le[ydes], ri[ydes]) >= ans1);
				// a new scheme is found
			}
			for (int j = 0; j < tot - 1; j++) {
				if (min(j + 1, tot - (j + 1)) < ans1) {
					continue;
				}
				int desy1 = ymap[xpoint[i][j].y];
				int desy2 = ymap[xpoint[i][j + 1].y];
				int res = queryCount(root, desy1 + 1, desy2 - 1);
				ans2 += res;
			}
		}
		cout << ans2 << "\n";
	}

	return 0;
}