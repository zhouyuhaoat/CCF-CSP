/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-25 10:08:01
 * 	modified: 	2024-05-25 11:44:29
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

const int maxn = 102;
int p[maxn][maxn]; // adjacent difference: inverse of prefix/partial sum

void insert(int x1, int y1, int x2, int y2) { // 2-dim difference
	++p[x1][y1];
	--p[x1][y2 + 1];
	--p[x2 + 1][y1];
	++p[x2 + 1][y2 + 1];
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	for (int q = 0; q < n; q++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		insert(x1 + 1, y1 + 1, x2, y2); // 1-based
	}
	int cnt = 0;
	for (int i = 1; i < maxn; i++) {
		for (int j = 1; j < maxn; j++) {
			p[i][j] += p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1]; // prefix sum
			if (p[i][j] > 0) {
				++cnt;
			}
		}
	}
	cout << cnt << "\n";

	return 0;
}