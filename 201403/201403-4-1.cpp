/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-22 18:35:04
 * 	modified: 	2024-05-24 20:20:40
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

int n, m, k, r;
vector<pair<int, int>> p; // point: x, y
vector<vector<int>> g, d; // d[destination][new router] = shortest distance

bool isok(pair<int, int> a, pair<int, int> b) {
	int dx = a.first - b.first, dy = a.second - b.second;
	return (long long)dx * dx + (long long)dy * dy <= (long long)r * r; // must be long long
	// return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2)) <= r; //cmath
}

void bfs(int s) {
	d[s][0] = 0;
	queue<pair<int, int>> q; // point/end/destination, cnt of new router
	q.emplace(s, 0);
	while (!q.empty()) {
		pair<int, int> t = q.front();
		q.pop();
		int u = t.first, cnt = t.second;
		for (auto v : g[u]) {
			if (v >= n) { // new router
				if (cnt < k && d[v][cnt + 1] > d[u][cnt] + 1) {
					d[v][cnt + 1] = d[u][cnt] + 1;
					q.emplace(v, cnt + 1);
				} // cnt >= k: nothing to do
			} else if (d[v][cnt] > d[u][cnt] + 1) { // existed router
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
	bfs(0);
	int ans = 0x3fffffff;
	for (int i = 0; i <= k; i++) {
		ans = min(ans, d[1][i]);
	}
	cout << ans - 1 << "\n";

	return 0;
}