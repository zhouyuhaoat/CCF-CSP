/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-18 15:57:15
 * 	modified: 	2024-07-13 19:50:02
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

bool dp[301][301][301];
int ndv[301][301][301];
// next direction value

int main(int argc, char const *argv[]) {

	int n, m = 0;
	cin >> n;
	vector<int> d(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
		m = max(m, d[i] * 3 + 5);
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			if ((i + j) / 2 == d[n]) {
				dp[n - 1][i][j] = true;
				ndv[n - 1][i][j] = 0;
			}
		}
	}
	for (int i = n - 1; i >= 2; i--) {
		for (int k = 1; k <= m; k++) {
			for (int l = m; l >= 1; l--) {
				if (dp[i][k][l]) {
					for (int j = 1; j <= m; j++) {
						if ((j + k + l) / 3 == d[i]) {
							dp[i - 1][j][k] = true;
							ndv[i - 1][j][k] = l;
						}
					}
				}
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			if (dp[1][i][j] && (i + j) / 2 == d[1]) {
				cout << i;
				for (int k = 2; k <= n; k++) {
					cout << " " << j;
					int temp = ndv[k - 1][i][j];
					i = j;
					j = temp;
				}
				cout << "\n";
				return 0;
			}
		}
	}

	return 0;
}