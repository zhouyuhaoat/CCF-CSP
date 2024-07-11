/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 20:00:47
 * 	modified: 	2024-07-11 07:48:06
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

void bfs(int s, vector<vector<int>> &g, vector<bool> &vis) {
	queue<int> q;
	q.emplace(s);
	vis[s] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < (int)g[u].size(); i++) {
			if (!vis[g[u][i]]) {
				vis[g[u][i]] = true;
				q.emplace(g[u][i]);
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	vector<vector<int>> to(n + 1), from(n + 1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		to[a].emplace_back(b);
		from[b].emplace_back(a);
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		vector<bool> vis1(n + 1), vis2(n + 1);
		bfs(i, to, vis1);
		bfs(i, from, vis2);
		int cnt = 0;
		for (int j = 1; j <= n; j++) {
			if (vis1[j] || vis2[j]) {
				// can not directly count visited and judge cnt >= n - 1
				// since possible exist bi-directional edge
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