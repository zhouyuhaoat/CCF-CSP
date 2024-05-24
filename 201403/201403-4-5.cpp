/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-23 20:06:38
 * 	modified: 	2024-05-23 20:37:32
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

struct node {
	int x, y;
};

int n, m, k, r;
vector<node> p;
vector<bool> vis;
vector<vector<int>> g, d;

double dis(node a, node b) {
	double x = a.x - b.x, y = a.y - b.y;
	return sqrt(x * x + y * y);
}

void spfa(int s) { // shortest path faster algorithm
	d[s][0] = 0;
	queue<int> q;
	q.emplace(s);
	vis[s] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int h = 0; h <= k; h++) {
			if (d[u][h] != -1) {
				for (int v : g[u]) {
					if (v >= n) { // differentiate v >= n && v < n
						if (h < k && (d[v][h + 1] == -1 || d[v][h + 1] >= d[u][h] + 1)) {
							d[v][h + 1] = d[u][h] + 1;
							if (!vis[v]) {
								q.emplace(v);
								vis[v] = true;
							}
						}
					} else if (d[v][h] == -1 || d[v][h] >= d[u][h] + 1) {
						d[v][h] = d[u][h] + 1;
						if (!vis[v]) {
							q.emplace(v);
							vis[v] = true;
						}
					}
				}
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	cin >> n >> m >> k >> r;
	for (int i = 0; i < n + m; i++) {
		int x, y;
		cin >> x >> y;
		p.emplace_back(node{x, y});
	}
	g.resize(n + m);
	for (int i = 0; i < n + m; i++) {
		for (int j = i + 1; j < n + m; j++) {
			if (dis(p[i], p[j]) <= (double)r) {
				g[i].emplace_back(j);
				g[j].emplace_back(i);
			}
		}
	}
	vis.resize(n + m);
	d.resize(n + m, vector<int>(k + 1, -1));
	spfa(0);
	int res = -1;
	for (int i = 0; i <= k; i++) {
		if (d[1][i] != -1) {
			res = (res == -1 ? d[1][i] : min(res, d[1][i]));
		}
	}
	cout << res - 1 << "\n";

	return 0;
}