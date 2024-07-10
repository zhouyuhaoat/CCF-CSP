/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-09 21:55:41
 * 	modified: 	2024-07-10 15:50:17
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

const int maxn = 5010, maxm = 5010;

int ver[maxm][maxn], hor[maxm][maxn];
long long ans[maxn];

int A, B, Q, X;
int generate() {
	X = ((long long)A * X + B) % Q;
	return X;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m >> A >> B >> Q >> X;
	for (int i = 1; i < n; i++) { // 1 ~ n - 1 & 1 ~ m
		for (int j = 1; j <= m; j++) {
			// source -> sink: from top to bottom
			// transpose: ver -> horizontal; hor -> vertical
			ver[j][i] = generate();
		}
	}
	for (int i = 1; i < n - 1; i++) { // 1 ~ n - 2 & 1 ~ m - 1
		for (int j = 1; j < m; j++) {
			hor[j][i] = generate();
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j < n; j++) { // from top to bottom
			ans[j] += ver[i][j];
		}
		for (int j = 1; j < n - 1; j++) { // from left to right
			ans[j + 1] = min(ans[j + 1], ans[j] + hor[i][j]);
		}
		for (int j = n - 2; j >= 1; j--) { // from right to left
			ans[j] = min(ans[j], ans[j + 1] + hor[i][j]);
		}
	}
	cout << ans[1] << "\n";

	return 0;
}