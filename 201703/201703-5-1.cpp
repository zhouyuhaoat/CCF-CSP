/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-09 21:43:56
 * 	modified: 	2024-07-10 16:15:18
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
/*
maximum flow + planar graph
1. max-flow min-cut theorem
2. planar graph -> dual graph
*/
#include <iostream>

using namespace std;

const int maxn = 5010;

int row[maxn][maxn], col[maxn][maxn];
long long ans[maxn];

int A, B, Q, X;
int generate() {
	X = ((long long)A * X + B) % Q;
	return X;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m >> A >> B >> Q >> X;
	for (int i = 1; i <= n - 1; i++) { // 1 ~ n - 1 & 1 ~ m
		for (int j = 1; j <= m; j++) {
			col[i][j] = generate();
		}
	}
	for (int i = 2; i <= n - 1; i++) { // 2 ~ n - 1 & 1 ~ m - 1
		for (int j = 1; j <= m - 1; j++) {
			row[i][j] = generate();
		}
	}
	// source -> sink: from left to right
	// ans[1 ~ n - 1][1 ~ m]: shortest path from source to [1 ~ n - 1][1 ~ m]
	// state compression: from left to right, column by column
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i < n; i++) { // from left to right
			ans[i] += col[i][j];
		}
		for (int i = 2; i < n; i++) { // from top to bottom
			ans[i] = min(ans[i], ans[i - 1] + row[i][j]);
		}
		for (int i = n - 2; i >= 0; i--) { // from bottom to top
			ans[i] = min(ans[i], ans[i + 1] + row[i + 1][j]);
		}
	}
	cout << ans[1] << "\n";

	return 0;
}