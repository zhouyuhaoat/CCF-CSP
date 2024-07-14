/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-18 14:07:35
 * 	modified: 	2024-07-13 19:46:28
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
/*
Difference Constraints
SPFA: Shortest Path Faster Algorithm
*/
#include <climits>
#include <iostream>
#include <queue>

using namespace std;

using edge = vector<vector<pair<int, int>>>;

class graph {
  public:
	int n;
	edge e;
	vector<bool> inq;
	vector<int> dist, cnt;
	graph(int n) : n(n), e(n), inq(n), dist(n, INT_MIN), cnt(n) {
	}
	void addedge(int u, int v, int w) {
		e[u].emplace_back(v, w);
	}
	bool spfa(int sta) {
		queue<int> q;
		q.emplace(sta);
		inq[sta] = true;
		dist[sta] = 0;
		cnt[sta]++;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for (auto it : e[u]) {
				int v = it.first, w = it.second;
				if (dist[v] < dist[u] + w) {
					dist[v] = dist[u] + w;
					if (!inq[v]) {
						q.emplace(v);
						inq[v] = true;
						if (++cnt[v] == n) {
							return false;
						}
					}
				}
			}
		}
		return true;
	}
};

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<int> d(n + 1);
	for (int i = 0; i < n; i++) {
		cin >> d[i + 1];
	}
	graph g(n + 1);
	g.addedge(0, 2, 2 * d[1]);
	g.addedge(2, 0, -(2 * d[1] + 1));
	g.addedge(n - 2, n, 2 * d[n]);
	g.addedge(n, n - 2, -(2 * d[n] + 1));
	for (int i = 2; i < n; i++) {
		g.addedge(i - 2, i + 1, 3 * d[i]);
		g.addedge(i + 1, i - 2, -(3 * d[i] + 2));
	}
	for (int i = 1; i <= n; i++) {
		g.addedge(i - 1, i, 1);
	}
	g.spfa(0);
	for (int i = 1; i < (int)g.dist.size(); i++) {
		cout << g.dist[i] - g.dist[i - 1];
		i < g.dist.size() - 1 ? cout << " " : cout << "\n";
	}

	return 0;
}