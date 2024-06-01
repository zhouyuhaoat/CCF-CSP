/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-28 15:08:31
 * 	modified: 	2024-05-28 22:29:29
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int dia = 0;
vector<int> d; // depth or distance
vector<vector<int>> g;

void dfs(int u, int fa) {
	for (auto v : g[u]) {
		if (v == fa) {
			continue;
		}
		d[v] = d[u] + 1;
		if (d[v] > d[dia]) {
			dia = v;
		}
		dfs(v, u);
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	g.resize(n + m + 1);
	d.resize(n + m + 1);
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
	d[dia] = 0;
	dfs(dia, 0);
	cout << d[dia] << "\n";

	return 0;
}