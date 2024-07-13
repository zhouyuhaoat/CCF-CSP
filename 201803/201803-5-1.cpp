/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-13 10:35:29
 * 	modified: 	2024-07-13 19:00:10
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

const int maxn = 100010, maxm = maxn * 2, mod = 1e9 + 7;

struct node {
	int d, w, id;
	bool operator<(const node &t) const {
		return d < t.d;
	}
} q[maxn], p[maxn];

int h[maxn], e[maxm], ne[maxm], idx;
void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int tr[maxn];
// Binary Indexed Tree or Fenwick Tree
// BIT: lowbit + update + query

int lowbit(int x) {
	return x & -x;
}

void update(int x, int v, int k) {
	for (int i = x; i <= k; i += lowbit(i)) {
		tr[i] = (tr[i] + v) % mod;
	}
}

int query(int x, int k) {
	x = min(x, k); // why min?
	int res = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		res = (res + tr[i]) % mod;
	}
	return res;
}

int depth[maxn], fa[maxn][17];
// lowest common ancestor: depth + ancestor
// ancestor: array doubling, or binary lifting

void bfs() {
	memset(depth, 0x3f, sizeof(depth));
	depth[0] = 0, depth[1] = 1;
	queue<int> que;
	que.emplace(1);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = h[u]; ~i; i = ne[i]) {
			int v = e[i];
			if (depth[v] > depth[u] + 1) {
				depth[v] = depth[u] + 1;
				que.emplace(v);
				fa[v][0] = u;
				for (int k = 1; k <= 16; k++) {
					fa[v][k] = fa[fa[v][k - 1]][k - 1];
				}
			}
		}
	}
}

int lca(int a, int b) {
	if (depth[a] < depth[b]) {
		swap(a, b);
	}
	for (int k = 16; k >= 0; k--) {
		if (depth[fa[a][k]] >= depth[b]) {
			a = fa[a][k];
		}
	}
	if (a == b) {
		return a;
	}
	for (int k = 16; k >= 0; k--) {
		if (fa[a][k] != fa[b][k]) {
			a = fa[a][k], b = fa[b][k];
		}
	}
	return fa[a][0];
}

int path[maxn], d[maxn];

void dfs(int u, int fa) {
	d[u] = (d[fa] + path[u]) % mod;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == fa) {
			continue;
		}
		dfs(v, u);
	}
}

bool vis[maxn];

int getsize(int u, int fa) { // subtree, or connected component
	if (vis[u]) {
		return 0;
	}
	int res = 1;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v != fa) {
			res += getsize(v, u);
		}
	}
	return res;
}

int getwc(int u, int fa, int tot, int &wc) { // weight center
	if (vis[u]) {
		return 0;
	}
	int sum = 1, ms = 0; // max sum
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == fa) {
			continue;
		}
		int t = getwc(v, u, tot, wc);
		ms = max(ms, t);
		sum += t;
	}
	ms = max(ms, tot - sum); // total
	if (ms <= tot / 2) {
		wc = u;
	}
	return sum;
}

int w[maxn]; // weight

void getdist(int u, int fa, int dist, int sum, int &qt) { // distance
	if (vis[u]) {
		return;
	}
	q[++qt] = {dist, sum, u};
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v != fa) {
			getdist(v, u, dist + 1, (sum + w[v]) % mod, qt);
		}
	}
}

int get(node a[], int k, int limit, int wu, int &pu) {
	sort(a + 1, a + k + 1);
	static int sum[maxn]; // prefix sum
	for (int i = 1; i <= k; i++) {
		sum[i] = (sum[i - 1] + a[i].w) % mod;
	}
	int res = 0;
	for (int i = 1, j = k; i < j; i++) { // double pointer
		while (j > i && a[j].d + a[i].d - 1 > limit) {
			j--;
		}
		if (j > i && a[j].d + a[i].d - 1 <= limit) {
			res = (res + sum[j] - sum[i] + (ll)(a[i].w - wu) * (j - i)) % mod;
			pu = (pu + j - i) % mod;
		}
	}
	return res;
}

int L, R;

int dfspath(int u, int fa, int dist, int maxd) {
	if (vis[u]) {
		return 0;
	}
	int res = (query(R + 1 - dist, maxd) - query(L - dist, maxd)) % mod;
	if (dist >= L && dist <= R) {
		res = (res + 1) % mod;
	}
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v != fa) {
			res = (res + dfspath(v, u, dist + 1, maxd)) % mod;
		}
	}
	path[u] = (path[u] + res) % mod;
	return res;
}

int pos[maxn], root[maxn];

int calc(int u) {
	if (vis[u]) {
		return 0;
	}
	getwc(u, -1, getsize(u, -1), u);
	vis[u] = true;
	int res = 0, pt = 0;
	if (L <= 1 && R >= 1) {
		res = w[u], path[u] = (path[u] + 1) % mod;
	}
	int cnt = 0, maxd = 0;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i], qt = 0;
		if (vis[v]) {
			continue;
		}
		getdist(v, -1, 2, (w[u] + w[v]) % mod, qt);
		int pL = 0, pR = 0;
		res = (res - (ll)(get(q, qt, R, w[u], pR) - get(q, qt, L - 1, w[u], pL))) % mod;
		path[u] = (path[u] - (ll)(pR - pL)) % mod;
		pos[++cnt] = pt + 1; // start of each segment
		root[cnt] = v;		 // root of each segment
		for (int k = 1; k <= qt; k++) {
			if (q[k].d >= L && q[k].d <= R) {
				res = (res + q[k].w) % mod;
				path[u] = (path[u] + 1) % mod; // only calculate from u to the current node
			}
			p[++pt] = q[k];
			maxd = max(maxd, q[k].d);
		}
	}
	pos[cnt + 1] = pt + 1; // sentinel
	for (int i = 1; i <= maxd; i++) {
		tr[i] = 0;
	}
	for (int i = 1; i <= pt; i++) {
		update(p[i].d, 1, maxd); // insert element into fenwick tree
	}
	for (int i = 1; i <= cnt; i++) {
		int l = pos[i], r = pos[i + 1] - 1;
		for (int j = l; j <= r; j++) {
			update(p[j].d, -1, maxd); // remove nodes from current subtree
		}
		dfspath(root[i], u, 2, maxd);
		for (int j = l; j <= r; j++) {
			update(p[j].d, 1, maxd); // restore removed nodes
		}
	}
	int pL = 0, pR = 0;
	res = (res + (ll)get(p, pt, R, w[u], pR) - get(p, pt, L - 1, w[u], pL)) % mod;
	path[u] = (path[u] + (ll)pR - pL) % mod;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		res = (res + calc(v)) % mod;
	}
	return res;
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m >> L >> R;
		memset(h, -1, sizeof(h)), idx = 0;
		memset(path, 0, sizeof(path));
		for (int i = 1; i <= n; i++) {
			cin >> w[i];
		}
		for (int i = 2; i <= n; i++) {
			int p;
			cin >> p;
			add(i, p), add(p, i);
		}
		memset(vis, 0, sizeof(vis));
		int res = calc(1);
		dfs(1, 0);
		bfs();
		while (m--) {
			int a, b, c;
			cin >> a >> b >> c;
			int p = lca(a, b);
			int sum = ((ll)d[a] + d[b] - (ll)d[p] * 2 + path[p]) * c % mod;
			res = ((res + sum) % mod + mod) % mod;
			cout << res << "\n";
		}
	}

	return 0;
}