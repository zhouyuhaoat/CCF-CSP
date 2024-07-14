/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-14 12:54:25
 * 	modified: 	2024-07-14 13:34:09
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 210, maxm = (500 + maxn) * 2 + 10, inf = 1e6;

int h[maxn], e[maxm], f[maxm], w[maxm], ne[maxm], idx;
int dis[maxn], pre[maxn], incf[maxn];
bool vis[maxn];
int din[maxn], dout[maxn];

void add(int a, int b, int c, int d) {
	e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

bool spfa(int sta, int end) {
	memset(dis, 0x3f, sizeof(dis));
	memset(incf, 0, sizeof(incf));
	queue<int> q;
	q.emplace(sta);
	dis[sta] = 0, incf[sta] = inf;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = h[u]; ~i; i = ne[i]) {
			int v = e[i];
			if (f[i] != 0 && dis[v] > dis[u] + w[i]) {
				dis[v] = dis[u] + w[i];
				pre[v] = i;
				incf[v] = min(f[i], incf[u]);
				if (!vis[v]) {
					q.emplace(v);
					vis[v] = true;
				}
			}
		}
	}
	return incf[end] > 0;
}

int ek(int tot, int sta, int end) {
	int flow = 0, cost = 0;
	while (spfa(sta, end)) {
		int t = incf[end];
		flow += t, cost += t * dis[end];
		for (int i = end; i != sta; i = e[pre[i] ^ 1]) {
			f[pre[i]] -= t;
			f[pre[i] ^ 1] += t;
		}
	}
	if (flow != tot) {
		return -1;
	}
	return cost;
}

int main(int argc, char const *argv[]) {

	int t, s, e;
	cin >> t >> s >> e;
	while (t--) {
		memset(h, -1, sizeof(h)), idx = 0;
		memset(din, 0, sizeof(din));
		memset(dout, 0, sizeof(dout));
		int n, m;
		cin >> n >> m;
		int sta = 0, end = n + 1;
		int downcost = 0;
		while (m--) {
			int a, b;
			char c;
			cin >> a >> b >> c;
			int down, up;
			if (c == 'A') {
				down = 1, up = inf, downcost += e;
			} else if (c == 'B') {
				down = up = 1, downcost += e;
			} else if (c == 'C') {
				down = 0, up = inf;
			} else {
				down = 0, up = 1;
			}
			add(a, b, up - down, e);
			din[b] += down, dout[a] += down;
		}
		int tot = 0;
		for (int i = 1; i <= n; i++) {
			if (din[i] > dout[i]) {
				add(sta, i, din[i] - dout[i], 0);
				tot += din[i] - dout[i];
			} else {
				add(i, end, dout[i] - din[i], 0);
			}
		}
		int cost = ek(tot, sta, end);
		if (cost != -1) {
			cost += downcost;
		}
		cout << cost << "\n";
	}

	return 0;
}