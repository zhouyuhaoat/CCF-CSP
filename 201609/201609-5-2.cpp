/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-06 16:23:42
 * 	modified: 	2024-07-07 12:39:33
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 300010;

#define x first
#define y second
typedef pair<int, int> pii;
pii p[maxn];
// ii: int -> int

struct node {
	int l, r, v, c;
	// v: point value
	// c: interval sum
} t[maxn << 2];

int level = 0, down[maxn], up[maxn];
// count points in the down and up of the point in x-axis
vector<int> discre;

int find(int x) { // get the index in discretized array
	return lower_bound(discre.begin(), discre.end(), x) - discre.begin();
}

void pushup(int u) {
	auto &l = t[u << 1], &r = t[u << 1 | 1];
	t[u].v = max(l.v, r.v);
	t[u].c = l.c + r.c;
}

void build(int u, int l, int r) {
	t[u] = {l, r};
	if (l == r) {
		t[u].v = t[u].c = 0;
	} else {
		int mi = (l + r) >> 1;
		build(u << 1, l, mi);
		build(u << 1 | 1, mi + 1, r);
		pushup(u);
	}
}

void update(int u, int x) { // modify
	if (t[u].l == t[u].r) { // interval -> point
		t[u].v = min(down[x], up[x]);
		t[u].c = t[u].v >= level;
		return;
	}
	int mid = (t[u].l + t[u].r) >> 1;
	if (x <= mid) {
		update(u << 1, x);
	} else {
		update(u << 1 | 1, x);
	}
	pushup(u);
}

pii query(int u, int l, int r) { // query return pair
	if (l <= t[u].l && r >= t[u].r) {
		return {t[u].v, t[u].c};
	}
	int mid = (t[u].l + t[u].r) >> 1;
	pii res(-1, 0);
	if (l <= mid) {
		res = query(u << 1, l, r);
	}
	if (r > mid) {
		auto t = query(u << 1 | 1, l, r);
		res.x = max(res.x, t.x);
		res.y += t.y;
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		cin >> p[i].x >> p[i].y;
		discre.emplace_back(p[i].x);
	}
	sort(discre.begin(), discre.end());
	discre.erase(unique(discre.begin(), discre.end()), discre.end());
	// discretize: sort and remove (or erase) duplicate elements
	// unique: remove (but not erase) duplicate elements to the end
	// unique: return the iterator pointing to the first duplicate element
	for (int i = 0; i < n; i++) {
		p[i].x = find(p[i].x);
		++down[p[i].x]; // enumerate from top to bottom in y-axis
	}
	sort(p, p + n, [](const pii &a, const pii &b) {
		if (a.y != b.y) {
			return a.y > b.y; // sort from top to bottom in y-axis
		}
		return a.x < b.x; // sort from left to right in x-axis
	});
	// after sorting, p consists of mutiple segments
	// each segment has a same y-axis value, increased x-axis value
	// that is each segment is a row
	build(1, 0, discre.size() - 1); // build segment tree in x-axis
	for (int i = 0; i < n; i++) {
		int j = i;
		while (j < n && p[j].y == p[i].y) { // one row
			int x = p[j++].x;
			--down[x], ++up[x];
			update(1, x); // update level
		}
		for (int k = i; k + 1 < j; k++) {
			if (p[k].x + 1 <= p[k + 1].x - 1) { // interval !empty
				auto t = query(1, p[k].x + 1, p[k + 1].x - 1);
				level = max(level, min(t.x, min(k - i + 1, j - k - 1)));
				// row: i -> j: left: i -> k; right: k + 1 -> j
			}
		}
		i = j - 1; // next row
	}
	if (q == 1) {
		cout << level << "\n";
	} else {
		memcpy(down, up, sizeof(up));
		// swap down and up, since scan line from top to bottom
		memset(up, 0, sizeof(up));
		build(1, 0, discre.size() - 1); // again
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			int j = i;
			while (j < n && p[j].y == p[i].y) {
				int x = p[j++].x;
				--down[x], ++up[x];
				update(1, x); // update scheme
			}
			for (int k = i; k + 1 < j; k++) {
				if (k - i + 1 >= level && j - k - 1 >= level && p[k].x + 1 <= p[k + 1].x - 1) {
					// left and right must not less than level
					auto t = query(1, p[k].x + 1, p[k + 1].x - 1);
					cnt += t.y;
				}
			}
			i = j - 1;
		}
		cout << cnt << "\n";
	}

	return 0;
}