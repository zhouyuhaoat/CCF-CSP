/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-02 22:04:14
 * 	modified: 	2024-05-25 14:39:16
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

struct node {
	int x, y;
	int d;
};

int X[4] = {0, 0, -1, 1}, Y[4] = {1, -1, 0, 0};
queue<node> q;
vector<vector<int>> w;
vector<vector<bool>> cus, vis;

bool islaw(int n, node p) {
	if (p.x >= 1 && p.x <= n && p.y >= 1 && p.y <= n && !vis[p.x][p.y]) {
		return true;
	}
	return false;
}

long long bfs(int n) {
	long long res = 0;
	while (!q.empty()) {
		node t = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			node nt = {t.x + X[i], t.y + Y[i], t.d + 1};
			if (islaw(n, nt)) {
				q.emplace(nt);
				vis[nt.x][nt.y] = true; // visit through shortest path
				if (cus[nt.x][nt.y]) {
					res += w[nt.x][nt.y] * nt.d;
				}
			}
		}
	}
	return res;
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(false); // necessary for fast I/O
	cin.tie(0);
	int n, m, k, d;
	cin >> n >> m >> k >> d;
	w.resize(n + 1, vector<int>(n + 1));
	cus.resize(n + 1, vector<bool>(n + 1));
	vis.resize(n + 1, vector<bool>(n + 1));
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		vis[x][y] = true;
		q.emplace(node{x, y, 0}); // multi-source bfs
	}
	for (int i = 0; i < k; i++) {
		int x, y, ww;
		cin >> x >> y >> ww;
		cus[x][y] = true;
		w[x][y] += ww;
	}
	for (int i = 0; i < d; i++) {
		int x, y;
		cin >> x >> y;
		vis[x][y] = true;
	}
	cout << bfs(n) << "\n";

	return 0;
}