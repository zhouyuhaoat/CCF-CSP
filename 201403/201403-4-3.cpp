/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-23 12:38:06
 * 	modified: 	2024-05-23 20:25:54
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

int n, m, k, r;
vector<pair<int, int>> p;
vector<vector<bool>> vis;
vector<vector<int>> g, d;

bool isok(pair<int, int> a, pair<int, int> b) {
	int dx = a.first - b.first, dy = a.second - b.second;
	return (long long)dx * dx + (long long)dy * dy <= (long long)r * r;
}

void bfs(int s) {
	d[s][0] = 0;
	queue<pair<int, int>> q;
	q.emplace(s, 0);
	while (!q.empty()) {
		pair<int, int> t = q.front();
		q.pop();
		int u = t.first, cnt = t.second;
		if (vis[u][cnt]) { // pruning
			continue;
		}
		vis[u][cnt] = true;
		for (auto v : g[u]) {
			if (v >= n) {
				if (cnt < k && d[v][cnt + 1] > d[u][cnt] + 1) {
					d[v][cnt + 1] = d[u][cnt] + 1;
					q.emplace(v, cnt + 1);
				}
			} else if (d[v][cnt] > d[u][cnt] + 1) {
				d[v][cnt] = d[u][cnt] + 1;
				q.emplace(v, cnt);
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	cin >> n >> m >> k >> r;
	p.resize(n + m);
	for (int i = 0; i < n + m; i++) {
		cin >> p[i].first >> p[i].second;
	}
	g.resize(n + m);
	for (int i = 0; i < n + m; i++) {
		for (int j = i + 1; j < n + m; j++) {
			if (isok(p[i], p[j])) {
				g[i].emplace_back(j);
				g[j].emplace_back(i);
			}
		}
	}
	d.resize(n + m, vector<int>(k + 1, 0x3fffffff));
	vis.resize(n + m, vector<bool>(k + 1));
	bfs(0);
	int ans = 0x3fffffff;
	for (int i = 0; i <= k; i++) {
		ans = min(ans, d[1][i]);
	}
	cout << ans - 1 << "\n";

	return 0;
}