/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-24 19:41:01
 * 	modified: 	2024-05-24 20:22:32
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

int n, m, k, r;
vector<pair<int, int>> p;
vector<vector<int>> g;
vector<int> d;

int point(int l, int v) {
	return (n + m) * l + v;
}

void build(int i, int j) { // bool -> int or flag
	for (int l = 0; l <= k; l++) {
		if (l + (j >= n) <= k) {
			g[point(l, i)].emplace_back(point(l + (j >= n), j));
		}
		if (l + (i >= n) <= k) {
			g[point(l, j)].emplace_back(point(l + (i >= n), i));
		}
	}
}

bool isok(pair<int, int> a, pair<int, int> b) {
	int dx = a.first - b.first, dy = a.second - b.second;
	return (long long)dx * dx + (long long)dy * dy <= (long long)r * r;
}

void bfs(int s) {
	d[point(0, s)] = 0;
	queue<int> q;
	q.emplace(point(0, s));
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : g[u]) {
			if (d[v] >= 0x3fffffff) {
				d[v] = d[u] + 1;
				q.emplace(v);
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
	g.resize((n + m) * (k + 1));
	for (int i = 0; i < n + m; i++) {
		for (int j = i + 1; j < n + m; j++) {
			if (isok(p[i], p[j])) {
				build(i, j), build(j, i);
			}
		}
	}
	d.resize((n + m) * (k + 1), 0x3fffffff);
	bfs(0);
	int ans = 0x3fffffff;
	for (int l = 0; l <= k; l++) {
		ans = min(ans, d[point(l, 1)]);
	}
	cout << ans - 1 << "\n";

	return 0;
}