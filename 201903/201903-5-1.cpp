/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 20:23:48
 * 	modified: 	2024-07-15 21:12:27
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 10010, maxm = 20010, maxc = 1010, inf = 0x3f3f3f3f;

int type[maxn];
int h[maxn], e[maxm], w[maxm], ne[maxm], idx;
int dis[maxn], d[maxn][maxc], cnt;
bool inq[maxn];

void add(int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void spfa(int sta, int n) {
	memset(dis, 0x3f, sizeof(dis)); // 0x3f3f3f3f, not 0x3fffffff
	dis[sta] = 0;
	queue<int> q;
	q.emplace(sta);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for (int i = h[u]; ~i; i = ne[i]) {
			int v = e[i];
			if (dis[v] > dis[u] + w[i]) {
				dis[v] = dis[u] + w[i];
				if (!inq[v]) {
					q.emplace(v);
					inq[v] = true;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		d[i][cnt] = dis[i]; // dimensionality increase
	}
}

int main(int argc, char const *argv[]) {

	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		cin >> type[i];
	}
	memset(h, -1, sizeof(h));
	while (m--) {
		int a, b, c;
		cin >> a >> b >> c;
		add(a, b, c), add(b, a, c);
	}
	for (int i = 1; i <= n; i++) {
		if (type[i] == 1) {
			spfa(i, n);
			// reverse traversal: from special node to normal node
			++cnt; // cnt: special node
		}
	}
	for (int i = 1; i <= n; i++) {
		int res = 0;
		sort(d[i], d[i] + cnt);
		for (int j = 0; j < k && j < cnt; j++) {
			if (d[i][j] != inf) {
				res += d[i][j];
			} else {
				break;
			}
		}
		cout << res << "\n";
	}

	return 0;
}