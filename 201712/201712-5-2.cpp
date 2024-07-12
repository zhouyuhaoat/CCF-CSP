/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-12 21:56:35
 * 	modified: 	2024-07-12 22:52:00
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// https://blog.csdn.net/weixin_44316314/article/details/119381524
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 1e5 + 5;

struct node {
	int id, val;
	node(int id, int val) : id(id), val(val) {
	}
};

vector<node> g[maxn];
ll v[maxn], f[maxn], dfn[maxn], num[maxn], siz[maxn], dis[maxn];
int cnt;
ll dp[maxn], mod = 1e18;

double A(int i, int j) {
	return (dp[i] - dis[i] * dis[i]) - (dp[j] - dis[j] * dis[j]);
}

double B(int i, int j) {
	return 2 * (dis[i] - dis[j]);
}

void dfs1(int x, ll d) {
	cnt++;
	dfn[x] = cnt;
	num[cnt] = x;
	dis[x] = d;
	siz[x] = 1;
	for (int i = 0; i < (int)g[x].size(); i++) {
		int t = g[x][i].id;
		dfs1(t, d + g[x][i].val);
		siz[x] += siz[t];
	}
}

struct nodex {
	int l, r, flag;
	vector<int> q, p;
} a[maxn * 4];

void update(int x) {
	int id1 = 0, id2 = 0;
	int l = 2 * x, r = 2 * x + 1;
	while (id1 < a[l].p.size() || id2 < a[r].p.size()) {
		int now;
		if (id1 == a[l].p.size()) {
			now = a[r].p[id2];
			id2++;
		} else if (id2 == a[r].p.size()) {
			now = a[l].p[id1];
			id1++;
		} else {
			if (dis[a[l].p[id1]] < dis[a[r].p[id2]]) {
				now = a[l].p[id1];
				id1++;
			} else {
				now = a[r].p[id2];
				id2++;
			}
		}
		a[x].p.emplace_back(now);
	}
}

void build(int x, int l, int r) {
	a[x].l = l, a[x].r = r;
	a[x].flag = 0;
	a[x].q.clear();
	a[x].p.clear();
	if (l == r) {
		a[x].q.emplace_back(num[l]);
		a[x].p.emplace_back(num[l]);
		return;
	}
	int m = (l + r) >> 1;
	build(2 * x, l, m);
	build(2 * x + 1, m + 1, r);
	update(x);
}

ll query(int x, int l, int r, int p) {
	if (a[x].l == l && a[x].r == r) {
		if (a[x].flag == 0) {
			for (int i = 0; i < (int)a[x].p.size(); i++) {
				int now = a[x].p[i];
				int flagx = 0;
				while (a[x].q.size() > 1) {
					int t1 = a[x].q.back();
					a[x].q.pop_back();
					int t2 = a[x].q.back();
					if (dis[now] == dis[t1]) {
						if (dp[now] < dp[t1]) {
							flagx = 1;
							a[x].q.emplace_back(t1);
							break;
						}
					} else if (A(now, t1) / B(now, t1) < A(t1, t2) / B(t1, t2)) {
						a[x].q.emplace_back(t1);
						break;
					}
				}
				if (flagx == 0) {
					a[x].q.emplace_back(now);
				}
			}
			a[x].flag = 1;
		}
		int lx = 0, rx = a[x].q.size() - 2;
		int res = a[x].q.size() - 1;
		while (lx <= rx) {
			int mid = (lx + rx) >> 1;
			int midx = mid + 1;
			if (A(a[x].q[midx], a[x].q[mid]) / B(a[x].q[midx], a[x].q[mid]) < -(dis[p] + f[p])) {
				res = mid;
				rx = mid - 1;
			} else {
				lx = mid + 1;
			}
		}
		res = a[x].q[res];
		return max((ll)0, dp[res] + v[p] - (f[p] - (dis[res] - dis[p])) * (f[p] - (dis[res] - dis[p])));
	}
	int m = (a[x].l + a[x].r) >> 1;
	if (r <= m) {
		return query(2 * x, l, r, p);
	} else if (l > m) {
		return query(2 * x + 1, l, r, p);
	} else {
		return max(query(2 * x, l, m, p), query(2 * x + 1, m + 1, r, p));
	}
}

void dfs2(int x) {
	if (siz[x] == 1) {
		dp[x] = 0;
		return;
	}
	for (int i = 0; i < (int)g[x].size(); i++) {
		int t = g[x][i].id;
		dfs2(t);
	}
	dp[x] = query(1, dfn[x] + 1, dfn[x] + siz[x] - 1, x);
	dp[x] %= mod;
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			g[i].clear();
			dp[i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			int fa;
			ll val;
			cin >> fa >> val >> v[i] >> f[i];
			if (fa == 0) {
				continue;
			} else {
				g[fa].emplace_back(i, val);
			}
		}
		dfs1(1, 0);
		build(1, 1, n);
		dfs2(1);
		ll ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += dp[i];
			ans %= mod;
		}
		cout << ans << "\n";
	}

	return 0;
}