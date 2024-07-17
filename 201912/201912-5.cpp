/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-16 21:17:23
 * 	modified: 	2024-07-16 21:45:45
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// https://www.acwing.com/activity/content/code/content/915512
#include <iostream>
#include <map>
#include <queue>
#pragma GCC optimize(2)

using namespace std;

typedef __int128 i128;
typedef unsigned long long ull;
const int maxn = 1000010, maxm = 33;
const ull mod = 2009731336725594113ull;

map<ull, int> v2id;
ull id2v[maxm], prod[maxn][maxm];
int g[maxm][maxm], id;

ull U[] = {
	314882150829468584ull,	427197303358170108ull,	1022292690726729920ull,
	1698479428772363217ull, 2006101093849356424ull,
};

struct node {
	int l, r, k;
	int s[maxm];
} tr[maxn << 2];

void init(int n) {
	queue<ull> q;
	q.emplace(1);
	v2id[1] = ++id;
	id2v[id] = 1;
	while (!q.empty()) {
		ull t = q.front();
		q.pop();
		for (int i = 0; i < 5; i++) {
			i128 r = (i128)t * U[i] % mod;
			if (v2id.count(r) == 0) {
				v2id[r] = ++id;
				id2v[id] = r;
				q.emplace(r);
			}
		}
	}
	for (int i = 1; i <= id; i++) {
		for (int j = 1; j <= id; j++) {
			g[i][j] = v2id[(i128)id2v[i] * id2v[j] % mod];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= id; j++) {
			prod[i][j] = (prod[i - 1][j] + id2v[j]) % mod;
		}
	}
}

void pushup(int u) {
	auto l = tr[u << 1].s, r = tr[u << 1 | 1].s;
	for (int i = 1; i <= id; i++) {
		tr[u].s[i] = l[i] + r[i];
	}
}

void eval(int u, int k) {
	static int tmp[maxm];
	for (int i = 1; i <= id; i++) {
		tmp[i] = tr[u].s[g[i][k]];
	}
	for (int i = 1; i <= id; i++) {
		tr[u].s[i] = tmp[i];
	}
	if (tr[u].k != 0) {
		tr[u].k = g[tr[u].k][k];
	} else {
		tr[u].k = k;
	}
}

void pushdown(int u) {
	int k = tr[u].k;
	if (k != 0) {
		eval(u << 1, k), eval(u << 1 | 1, k);
		tr[u].k = 0;
	}
}

void build(int u, int l, int r) {
	tr[u] = {l, r};
	if (l == r) {
		for (int i = 1; i <= id; i++) {
			tr[u].s[i] = prod[l][i] % 2019;
		}
		return;
	}
	int mi = (l + r) >> 1;
	build(u << 1, l, mi), build(u << 1 | 1, mi + 1, r);
	pushup(u);
}

void update(int u, int l, int r, int k) {
	if (tr[u].l >= l && tr[u].r <= r) {
		eval(u, k);
	} else {
		pushdown(u);
		int mi = (tr[u].l + tr[u].r) >> 1;
		if (l <= mi) {
			update(u << 1, l, r, k);
		}
		if (r > mi) {
			update(u << 1 | 1, l, r, k);
		}
		pushup(u);
	}
}

int query(int u, int l, int r) {
	if (tr[u].l >= l && tr[u].r <= r) {
		return tr[u].s[1];
	}
	pushdown(u);
	int mi = (tr[u].l + tr[u].r) >> 1, res = 0;
	if (l <= mi) {
		res = query(u << 1, l, r);
	}
	if (r > mi) {
		res += query(u << 1 | 1, l, r);
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	init(n);
	build(1, 1, n);
	while (m--) {
		int l, r;
		cin >> l >> r;
		int t = query(1, l, r);
		cout << t << "\n";
		update(1, l, r, t % 5 + 2);
	}

	return 0;
}