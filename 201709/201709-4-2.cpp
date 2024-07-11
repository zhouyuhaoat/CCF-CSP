/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 20:00:47
 * 	modified: 	2024-07-11 07:43:21
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

void dfs(int u, vector<vector<int>> &g, vector<bool> &vis) { // &: @important!
	vis[u] = true;
	for (int i = 0; i < (int)g[u].size(); i++) {
		int v = g[u][i];
		if (!vis[v]) {
			dfs(v, g, vis);
		}
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	vector<vector<int>> g1(n + 1), g2(n + 1); // transposed graph
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g1[a].emplace_back(b);
		g2[b].emplace_back(a);
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		vector<bool> vis1(n + 1), vis2(n + 1);
		dfs(i, g1, vis1);
		dfs(i, g2, vis2);
		int cnt = 0;
		for (int j = 1; j <= n; j++) {
			if (vis1[j] || vis2[j]) {
				++cnt;
			}
		}
		if (cnt == n) {
			++res;
		}
	}
	cout << res << "\n";

	return 0;
}