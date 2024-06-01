/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:53:02
 * 	modified: 	2024-05-28 14:40:09
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	int d[n][m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> d[i][j];
		}
	}
	for (int i = m - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			cout << d[j][i];
			j < n - 1 ? cout << " " : cout << "\n";
		}
	}

	return 0;
}