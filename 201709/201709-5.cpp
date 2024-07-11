/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-11 15:49:49
 * 	modified: 	2024-07-11 16:43:34
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

const int maxn = 100010, maxm = 1000010;

struct qry {
	int opt, l, r, v;
} q[maxn];

int w[maxn];
long long tr[maxn];
// BIT: binary indexed tree, Fenwic tree
// lowbit & update & query

set<int> vs;
set<int> pos[maxm];

int lowbit(int x) {
	return x & -x;
}

void update(int x, int v, int n) {
	for (int i = x; i <= n; i += lowbit(i)) {
		tr[i] += v;
	}
}

long long query(int x) {
	long long res = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		res += tr[i];
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		update(i, w[i], n);
	}
	for (int i = 0; i < m; i++) {
		int opt, l, r;
		cin >> opt >> l >> r;
		if (opt == 1) {
			int v;
			cin >> v;
			q[i] = {opt, l, r, v};
			if (v != 1) {
				vs.emplace(v);
			}
		} else {
			q[i] = {opt, l, r};
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j * j <= w[i]; j++) { // factor < or <= sqrt
			if (w[i] % j == 0) {
				if (vs.count(j) != 0) {
					pos[j].emplace(i); // position
				}
				if (w[i] / j != j && vs.count(w[i] / j) != 0) {
					pos[w[i] / j].emplace(i);
				}
			}
		}
	}
	for (int i = 0; i < m; i++) {
		if (q[i].opt == 1) {
			int v = q[i].v;
			auto it = pos[v].lower_bound(q[i].l);
			while (it != pos[v].end() && *it <= q[i].r) {
				int k = *it++;
				update(k, -w[k] + w[k] / v, n);
				for (int j = 1; j * j <= w[k]; j++) {
					if (w[k] % j == 0) {
						pos[j].erase(k);
						if (w[k] / j != j) {
							pos[w[k] / j].erase(k);
						}
					}
				}
				w[k] /= v; // maintain position of factor
				for (int j = 1; j * j <= w[k]; j++) {
					if (w[k] % j == 0) {
						if (vs.count(j) != 0) {
							pos[j].emplace(k);
						}
						if (w[k] / j != j && vs.count(w[k] / j) != 0) {
							pos[w[k] / j].emplace(k);
						}
					}
				}
			}
		} else {
			cout << query(q[i].r) - query(q[i].l - 1) << "\n";
		}
	}

	return 0;
}