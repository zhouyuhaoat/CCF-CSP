/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-01 13:30:54
 * 	modified: 	2024-05-21 21:15:00
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

struct node {
	int x, y;
} st, en;

int r, c;
int X[4] = {-1, 1, 0, 0}, Y[4] = {0, 0, -1, 1};
vector<vector<char>> g;
vector<vector<bool>> isarr, notarr;

bool islaw(node n) {
	if (n.x >= 0 && n.x < r && n.y >= 0 && n.y < c) {
		if (g[n.x][n.y] != '#') {
			return true;
		}
	}
	return false;
}

void bfs(node s) {
	queue<node> q;
	q.emplace(s);
	while (!q.empty()) {
		node t = q.front();
		q.pop();
		int l = 0, r = 4;
		switch (g[t.x][t.y]) {
			case '-':
				l = 2;
				break;
			case '|':
				r = 2;
				break;
			case '.':
				l = 1, r = 2;
				break;
		}
		for (int i = l; i < r; i++) {
			node n = {t.x + X[i], t.y + Y[i]};
			if (islaw(n) && !isarr[n.x][n.y]) {
				isarr[n.x][n.y] = true;
				q.emplace(n);
			}
		}
	}
}

void bfsrev(node s) {
	queue<node> q;
	q.emplace(s);
	while (!q.empty()) {
		node t = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			node n = {t.x + X[i], t.y + Y[i]};
			if (islaw(n) && !notarr[n.x][n.y]) {
				bool flag = false;
				switch (g[n.x][n.y]) {
					case '.':
						if (i == 0) {
							flag = true;
						}
						break;
					case '-':
						if (i == 2 || i == 3) {
							flag = true;
						}
						break;
					case '|':
						if (i == 0 || i == 1) {
							flag = true;
						}
						break;
					default:
						flag = true;
				}
				if (flag) {
					notarr[n.x][n.y] = true;
					q.emplace(n);
				}
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	cin >> r >> c;
	g.resize(r, vector<char>(c));
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> g[i][j];
			if (g[i][j] == 'S') {
				st = {i, j}, g[i][j] = '+';
			} else if (g[i][j] == 'T') {
				en = {i, j}, g[i][j] = '+';
			}
		}
	}
	isarr.resize(r, vector<bool>(c));
	bfs(st);
	if (!isarr[en.x][en.y]) {
		cout << "I'm stuck!\n";
	} else {
		notarr.resize(r, vector<bool>(c));
		bfsrev(en);
		int cnt = 0;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (isarr[i][j] && !notarr[i][j]) {
					++cnt;
				}
			}
		}
		cout << cnt << "\n";
	}

	return 0;
}