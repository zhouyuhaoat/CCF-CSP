/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-16 15:39:46
 * 	modified: 	2024-07-16 15:54:04
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <map>
#define x first
#define y second

using namespace std;

map<pair<int, int>, bool> t;
// 3-by-3 gird: 0, 1, 2, 3, 4, 5, 6, 7, 8
int dx[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int dy[9] = {1, 1, 1, 0, 0, 0, -1, -1, -1};

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	pair<int, int> c[n];
	for (int i = 0; i < n; i++) {
		cin >> c[i].x >> c[i].y;
		t[c[i]] = true;
	}
	int cnt[5] = {0};
	for (int i = 0; i < n; i++) {
		bool flag[9] = {false};
		for (int j = 0; j < 9; j++) {
			pair<int, int> p = {c[i].x + dx[j], c[i].y + dy[j]};
			flag[j] = t[p];
		}
		if (flag[4] && flag[1] && flag[3] && flag[5] && flag[7]) {
			++cnt[flag[0] + flag[2] + flag[6] + flag[8]];
		}
	}
	for (int i = 0; i < 5; i++) {
		cout << cnt[i] << "\n";
	}

	return 0;
}