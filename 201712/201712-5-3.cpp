/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-12 22:30:24
 * 	modified: 	2024-07-12 23:05:12
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// https://www.acwing.com/solution/content/87872
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll mod = 1e18, N = 1e5 + 5;

struct Edge {
	int t, s, ne;
} e[N];
int h[N], idx1;
void add(int u, int v, int s) {
	e[++idx1] = {v, s, h[u]}, h[u] = idx1;
}

ll v[N], f[N];
ll d[N], dp[N];
int sz[N], ind[N], idx2;

void dfs1(int from, ll s) {
	// first dfs: dfs order, distance to root, size of subtree
	ind[from] = ++idx2, d[idx2] = s, sz[from] = 1;
	for (int i = h[from]; i; i = e[i].ne) {
		dfs1(e[i].t, s + e[i].s);
		sz[from] += sz[e[i].t];
	}
}

#define sq(x) ((x) * (x))			 // square, x -> (x)
#define ff(x) (dp[x] - sq(d[x]))	 // convex hull point's y-coordinate value
#define dy(x1, x2) (ff(x1) - ff(x2)) // dy/dx slope
#define dx(x1, x2) (d[x1] - d[x2])	 // convex hull point's x-coordinate d[x], not separately defined if not needed

struct Node {
	bool vis;
	vector<int> q; // maintain the convex hull
	void build() { // construct the convex hull, in-place algorithm, one pass is enough
		int r = 0;
		for (int &i : q) {
			while (r > 1 && (double)dy(q[r - 1], q[r - 2]) * dx(i, q[r - 1]) <=
								(double)dy(i, q[r - 1]) * dx(q[r - 1], q[r - 2])) {
				r--;
			}
			q[r++] = i;
		}
		q.resize(r);
	}
	ll find(int i) { // binary search, passed i is original index, ind[i] is DFS order
		if (!vis) {
			vis = 1, build();
		}
		ll k = -2 * (f[i] + d[ind[i]]); // slope, remember to take negative
		int l = -1, r = q.size() - 1;	// if there is only one point, directly take r
		while (r - l > 1) {				// at least two points, binary search
			int mid = (l + r) >> 1;
			if ((double)dy(q[mid + 1], q[mid]) <= (double)k * dx(q[mid + 1], q[mid])) {
				r = mid; // r is certainly selectable
			} else {
				l = mid; // l is certainly not selectable
			}
		}
		return dp[q[r]] + v[i] - sq(f[i] + d[ind[i]] - d[q[r]]);
	}
} tr[N << 2];

#define cur tr[x]		   // current node
#define lch tr[x << 1]	   // left child node
#define rch tr[x << 1 | 1] // right child node
#define mid ((l + r) >> 1)

void merge(int x) { // merge sort's merge function
	cur.q.resize(lch.q.size() + rch.q.size());
	int i = 0, j = 0, k = 0;
	while (i < lch.q.size() || j < rch.q.size()) {
		if (i == lch.q.size()) {
			cur.q[k++] = rch.q[j++];
		} else if (j == rch.q.size()) {
			cur.q[k++] = lch.q[i++];
		} else if (d[lch.q[i]] <= d[rch.q[j]]) {
			cur.q[k++] = lch.q[i++];
		} else {
			cur.q[k++] = rch.q[j++];
		}
	}
}

void build(int x, int l, int r) { // construct segment tree
	cur.vis = 0;
	if (l == r) {
		cur.q.resize(1, l);
	} else {
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		merge(x);
	}
}

int L, R, n, T; // [L, R] is the query interval

ll query(int x, int l, int r, int i) {
	// [l, r] is the current node's maintained interval
	if (l >= L && r <= R) {
		return cur.find(i);
	} else {
		return max(mid >= L ? query(x << 1, l, mid, i) : 0, mid < R ? query(x << 1 | 1, mid + 1, r, i) : 0);
	}
}

void dfs2(int from) {
	if (!h[from]) {
		return;
	}
	// add reference, h array is discarded after use
	for (int &i = h[from]; i; i = e[i].ne) {
		dfs2(e[i].t);
	}
	// from is the original label, ind[from] is DFS order
	L = ind[from] + 1;
	R = ind[from] + sz[from] - 1;
	dp[ind[from]] = query(1, 1, n, from);
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		idx1 = idx2 = 0;
		cin >> n;
		for (int i = 1, u, s; i <= n; i++) {
			cin >> u >> s >> v[i] >> f[i];
			add(u, i, s);
		}
		dfs1(1, 0);
		build(1, 1, n);
		dfs2(1);
		ll ans = 0;
		// slope optimization cannot modulo dp values
		// otherwise it maintains no convex hull
		for (int i = 1; i <= n; i++) {
			ans = (ans + dp[i]) % mod, dp[i] = 0;
		}
		cout << ans << "\n";
	}

	return 0;
}