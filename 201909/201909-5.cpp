/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-16 14:08:50
 * 	modified: 	2024-07-16 14:49:31
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;
const int maxn = 50010, maxm = maxn << 1, maxk = 110;

int h[maxn], e[maxm], w[maxm], ne[maxm], idx;
bool flag[maxn];
int group[maxn]; // size of subtree -> group
ll f[maxn][maxk];
// f, func, function: tree dp
// f[root][number of special node] = shortest distance
// f[u][p] = min(f[u][p], f[u][p - q] + f[v][q] + w(u, v) * (p - q) * q)
// (p - q) * q: w(u, v) is the only edge between nodes in two group

void add(int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa, int k) {
	f[u][0] = 0;
	if (flag[u]) {
		f[u][1] = 0;
	}
	group[u] = 1;
	for (int i = h[u]; ~i; i = ne[i]) { // enumerate (item) groups
		int v = e[i];
		if (v == fa) {
			continue;
		}
		dfs(v, u, k);
		group[u] += group[v];
		// knapsack problem with groups
		for (int p = min(group[u], k); p >= 0; p--) {	  // enumerate volumes
			for (int q = 0; q <= min(p, group[v]); q++) { // enumerate decisions or choice
				f[u][p] = min(f[u][p], f[u][p - q] + f[v][q] + (ll)w[i] * q * (k - q));
				// total k, choose q, left k - q
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	int n, m, k;
	cin >> n >> m >> k;
	while (m--) {
		int x;
		cin >> x;
		flag[x] = true;
	}
	memset(h, -1, sizeof(h));
	for (int i = 0; i < n - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		add(a, b, c), add(b, a, c);
	}
	memset(f, 0x3f, sizeof(f));
	dfs(1, -1, k);
	cout << f[1][k] << "\n";

	return 0;
}