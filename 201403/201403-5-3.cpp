/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-24 10:29:25
 * 	modified: 	2024-05-24 15:31:32
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int a[n + 1], b[n + 1], c[n + 1], d[n + 1];
	int t = 0, ta = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		d[i] = min(b[i], d[i]);
		t += a[i];
		if (i & 1) {
			ta += a[i];
		}
	}
	t = max(ta, t - ta);
	int dp[t + 1][t + 1][t + 1]; // no scroll
	memset(dp, 0x7f, sizeof(dp));
	dp[0][0][0] = 0;
	for (int q = 1; q <= n; q++) {
		for (int i = t; i >= 0; i--) { // memorylessness: reverse rewrite
			for (int j = t; j >= i; j--) {
				for (int k = j; k >= 0; k--) {
					int &v = dp[i][j][k];
					v = dp[i][j][k] + d[q];
					if (i >= a[q]) {
						v = min(v, dp[i - a[q]][j][k]);
					}
					if (j >= a[q]) {
						v = min(v, dp[min(i, j - a[q])][max(i, j - a[q])][k]);
					}
					if (i >= c[q] && k >= c[q]) {
						v = min(v, dp[i - c[q]][j][k - c[q]]);
					}
					if (j >= c[q] && k >= c[q]) {
						v = min(v, dp[min(i, j - c[q])][max(i, j - c[q])][k - c[q]]);
					}
				}
			}
		}
	}
	int res = 0x7fffffff;
	for (int i = 0; i <= t; i++) {
		for (int j = i; j <= t; j++) {
			for (int k = 0; k <= j; k++) {
				res = min(res, dp[i][j][k] + j);
			}
		}
	}
	cout << res << "\n";

	return 0;
}