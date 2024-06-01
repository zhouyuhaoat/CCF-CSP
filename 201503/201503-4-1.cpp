/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:53:20
 * 	modified: 	2024-05-28 22:28:13
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int dia = -1; // diameter of tree: 2 dfs
vector<bool> vis;
vector<int> temp;
vector<vector<int>> g;

void dfs(int s, int l) {
	vis[s] = true;
	if (l > dia) {
		dia = l;
		temp.clear();
		temp.emplace_back(s);
	} else if (l == dia) {
		temp.emplace_back(s);
	}
	for (int i = 0; i < (int)g[s].size(); i++) {
		if (!vis[g[s][i]]) {
			dfs(g[s][i], l + 1);
		}
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	g.resize(n + m + 1);
	vis.resize(n + m + 1);
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
	fill(vis.begin(), vis.end(), false);
	dfs(temp[0], 0);
	cout << dia << "\n";

	return 0;
}