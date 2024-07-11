/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-10 21:46:29
 * 	modified: 	2024-07-10 21:48:56
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 1010, maxm = 20010;

int h1[maxn], h2[maxn], e[maxm], ne[maxm], idx; // idx = 0 or idx = 1
bool vis1[maxn], vis2[maxn];

void addedge(int h[], int a, int b) {
	e[++idx] = b, ne[idx] = h[a], h[a] = idx;
}

void dfs(int u, int h[], bool vis[]) {
	vis[u] = true;
	for (int i = h[u]; i > 0; i = ne[i]) {
		int v = e[i];
		if (!vis[v]) {
			dfs(v, h, vis);
		}
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		addedge(h1, a, b);
		addedge(h2, b, a);
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		memset(vis1, 0, sizeof(vis1));
		memset(vis2, 0, sizeof(vis2));
		dfs(i, h1, vis1);
		dfs(i, h2, vis2);
		int cnt = 0;
		for (int j = 1; j <= n; j++) {
			if (vis1[j] || vis2[j]) {
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