/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 20:14:35
 * 	modified: 	2024-06-17 20:09:34
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	vector<vector<int>> d(n, vector<int>(m));
	vector<vector<bool>> flag(n, vector<bool>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> d[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int cntr = 0;
			for (int k = 0; j + k < m; k++) {
				if (d[i][j] == d[i][j + k]) {
					++cntr;
				} else {
					break;
				}
			}
			if (cntr >= 3) {
				for (int k = 0; j + k < m; k++) {
					if (d[i][j] == d[i][j + k]) {
						flag[i][j + k] = true;
					} else {
						break;
					}
				}
			}
			int cntc = 0;
			for (int k = 0; i + k < n; k++) {
				if (d[i][j] == d[i + k][j]) {
					++cntc;
				} else {
					break;
				}
			}
			if (cntc >= 3) {
				for (int k = 0; i + k < n; k++) {
					if (d[i][j] == d[i + k][j]) {
						flag[i + k][j] = true;
					} else {
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			flag[i][j] ? cout << "0" : cout << d[i][j];
			j < m - 1 ? cout << " " : cout << "\n";
		}
	}

	return 0;
}