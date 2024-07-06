/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 16:55:02
 * 	modified: 	2024-06-20 19:04:33
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

struct node {
	int x, y, step;
};

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
vector<vector<vector<bool>>> vis;

int bfs(int n, int m) {
	queue<node> q;
	q.emplace(node{1, 1, 0});
	while (!q.empty()) {
		node u = q.front();
		q.pop();
		if (u.x == n && u.y == m) {
			return u.step;
		}
		for (int i = 0; i < 4; i++) {
			node v = {u.x + dx[i], u.y + dy[i], u.step + 1};
			if (v.x < 1 || v.x > n || v.y < 1 || v.y > m) {
				continue;
			}
			if (vis[v.x][v.y][v.step]) {
				continue;
			}
			vis[v.x][v.y][v.step] = true;
			q.emplace(v);
		}
	}
	return 0;
}

int main(int argc, char const *argv[]) {

	int n, m, t;
	cin >> n >> m >> t;
	// slow compare to static array
	vis.resize(n + 1, vector<vector<bool>>(m + 1, vector<bool>(n + m + 100)));
	for (int i = 0; i < t; i++) {
		int r, c, a, b;
		cin >> r >> c >> a >> b;
		for (int j = a; j <= b; j++) {
			vis[r][c][j] = true;
		}
	}
	cout << bfs(n, m) << "\n";

	return 0;
}