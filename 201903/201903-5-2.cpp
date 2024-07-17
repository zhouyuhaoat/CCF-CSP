/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 21:05:46
 * 	modified: 	2024-07-15 21:13:28
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// STL queue -> array queue
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 10010, maxm = 20010, maxc = 1010, inf = 0x3f3f3f3f;

int type[maxn];
int h[maxn], e[maxm], w[maxm], ne[maxm], idx;
int dis[maxn], q[maxn], d[maxn][maxc], cnt;
bool inq[maxn];

void add(int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void spfa(int sta, int n) {
	memset(dis, 0x3f, sizeof(dis));
	dis[sta] = 0;
	int hh = 0, tt = 1;
	q[0] = sta;
	while (hh != tt) {
		int u = q[hh++];
		if (hh == maxn) {
			hh = 0;
		}
		inq[u] = false;
		for (int i = h[u]; ~i; i = ne[i]) {
			int v = e[i];
			if (dis[v] > dis[u] + w[i]) {
				dis[v] = dis[u] + w[i];
				if (!inq[v]) {
					q[tt++] = v;
					if (tt == maxn) {
						tt = 0;
					}
					inq[v] = true;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		d[i][cnt] = dis[i];
	}
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
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
			++cnt;
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