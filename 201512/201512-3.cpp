/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 20:14:35
 * 	modified: 	2024-06-18 14:31:35
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

int m, n;
int X[4] = {-1, 1, 0, 0}, Y[4] = {0, 0, -1, 1};
vector<vector<char>> g;

bool isvis(pair<int, int> t, char ch) {
	if (t.first >= 0 && t.first < n && t.second >= 0 && t.second < m) {
		if (g[t.first][t.second] != '-' && g[t.first][t.second] != '|' && g[t.first][t.second] != '+') {
			if (g[t.first][t.second] != ch) {
				return true;
			}
		}
	}
	return false;
}

void bfs(pair<int, int> s, char ch) { // Flood Fill
	queue<pair<int, int>> q;
	q.emplace(s);
	g[s.first][s.second] = ch;
	while (!q.empty()) {
		pair<int, int> t = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			pair<int, int> nt = {t.first + X[i], t.second + Y[i]};
			if (isvis(nt, ch)) {
				g[nt.first][nt.second] = ch;
				q.emplace(nt);
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	int q;
	cin >> m >> n >> q;
	g.resize(n, vector<char>(m, '.'));
	for (int qq = 0; qq < q; qq++) {
		int flag;
		cin >> flag;
		if (flag == 0) {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			if (x1 == x2) {
				if (y1 > y2) {
					swap(y1, y2);
				}
				for (int i = y1; i <= y2; i++) {
					if (g[n - 1 - i][x1] == '+') {
						continue;
					} else if (g[n - 1 - i][x1] == '-') {
						g[n - 1 - i][x1] = '+';
					} else {
						g[n - 1 - i][x1] = '|';
					}
				}
			} else {
				if (x1 > x2) {
					swap(x1, x2);
				}
				for (int i = x1; i <= x2; i++) {
					if (g[n - 1 - y1][i] == '+') {
						continue;
					} else if (g[n - 1 - y1][i] == '|') {
						g[n - 1 - y1][i] = '+';
					} else {
						g[n - 1 - y1][i] = '-';
					}
				}
			}
		} else {
			int x, y;
			char ch;
			cin >> x >> y >> ch;
			bfs({n - 1 - y, x}, ch);
		}
	}
	for (auto u : g) {
		for (auto v : u) {
			cout << v;
		}
		cout << "\n";
	}

	return 0;
}