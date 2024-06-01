/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-28 17:34:16
 * 	modified: 	2024-05-28 22:38:28
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int dia = 0;
vector<int> dp; // longest
vector<vector<int>> g;

void dfs(int u, int fa) {
	for (int v : g[u]) {
		if (v == fa) {
			continue;
		}
		dfs(v, u);
		dia = max(dia, dp[u] + dp[v] + 1); // 1: w(u, v)
		dp[u] = max(dp[u], dp[v] + 1);
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	g.resize(n + m + 1);
	dp.resize(n + m + 1);
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