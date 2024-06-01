/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-28 23:18:01
 * 	modified: 	2024-06-01 19:48:00
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int dia = 0;
vector<vector<int>> g;

int dfs(int u, int fa) {
	int d1 = 0, d2 = 0; // longest & second longest
	for (int v : g[u]) {
		if (v == fa) {
			continue;
		}
		int d = dfs(v, u) + 1;
		if (d > d1) {
			d2 = d1, d1 = d;
		} else if (d > d2) {
			d2 = d;
		}
	}
	dia = max(dia, d1 + d2);
	return d1;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	g.resize(n + m + 1);
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