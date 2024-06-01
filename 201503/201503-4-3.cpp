/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-28 17:31:43
 * 	modified: 	2024-06-01 19:52:22
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int dia = 0;
vector<int> d1, d2; // tree dp: longest & second longest
// direction: from root to leaf
vector<vector<int>> g;

void dfs(int u, int fa) {
	d1[u] = d2[u] = 0;
	for (int v : g[u]) {
		if (v == fa) {
			continue;
		}
		dfs(v, u);
		int t = d1[v] + 1;
		if (t > d1[u]) {
			d2[u] = d1[u], d1[u] = t;
		} else if (t > d2[u]) {
			d2[u] = t;
		}
	}
	dia = max(dia, d1[u] + d2[u]);
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	g.resize(n + m + 1);
	d1.resize(n + m + 1);
	d2.resize(n + m + 1);
	for (int i = 0; i < n - 1; i++) {
		int f;
		cin >> f;
		g[f].emplace_back(i + 2);
		g[i + 2].emplace_back(f);
	}
	for (int i = 0; i < m; i++) {
		int f;
		cin >> f;
		g[f].emplace_back(i + 1 + n);
		g[i + 1 + n].emplace_back(f);
	}
	dfs(1, 0);
	cout << dia << "\n";

	return 0;
}