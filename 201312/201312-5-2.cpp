/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-21 16:56:37
 * 	modified: 	2024-05-21 21:16:34
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
int X[4] = {-1, 0, 1, 0}, Y[4] = {0, 1, 0, -1}; // 0: up, 1: right, 2: down, 3: left
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

bool isok(node n, int i) {
	char c = g[n.x][n.y];
	if (c == '+') {
		return true;
	} else if (c == '-' && i % 2 == 1) {
		return true;
	} else if (c == '|' && i % 2 == 0) {
		return true;
	} else if (c == '.' && i == 2) {
		return true;
	} else {
		return false;
	}
}

void dfs(node n) {
	isarr[n.x][n.y] = true;
	for (int i = 0; i < 4; i++) {
		node t = {n.x + X[i], n.y + Y[i]};
		if (islaw(t) && !isarr[t.x][t.y] && isok(n, i)) { // n, not t
			dfs(t);
		}
	}
}

void dfsrev(node n) {
	notarr[n.x][n.y] = true;
	for (int i = 0; i < 4; i++) {
		node t = {n.x + X[i], n.y + Y[i]};
		if (islaw(t) && !notarr[t.x][t.y] && isok(t, i ^ 2)) { // bitwise xor: reverse direction
			dfsrev(t);
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
	dfs(st);
	if (!isarr[en.x][en.y]) {
		cout << "I'm stuck!\n";
	} else {
		notarr.resize(r, vector<bool>(c));
		dfsrev(en);
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