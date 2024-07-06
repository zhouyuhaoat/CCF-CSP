/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 17:05:38
 * 	modified: 	2024-06-20 18:53:53
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int g[15][10], d[4][4];
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> g[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> d[i][j];
		}
	}
	int offset;
	cin >> offset;
	--offset;
	int down = 15;
	for (int j = 0; j < 4; j++) {
		int k = 0, i;
		for (i = 3; i >= 0; i--) {
			if (d[i][j] == 0) {
				++k;
			} else {
				break;
			}
		}
		if (i < 0) {
			continue;
		}
		for (i = 4; i < 15; i++) {
			if (g[i][j + offset] == 0) {
				++k;
			} else {
				break;
			}
		}
		down = min(down, k);
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (d[i][j] != 0) {
				g[i + down][j + offset] = 1;
			}
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			cout << g[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}