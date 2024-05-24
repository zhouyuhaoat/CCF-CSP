/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-23 18:08:41
 * 	modified: 	2024-05-24 15:24:32
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
	int dp[2][t + 1][t + 1][t + 1];
	memset(dp, 0x7f, sizeof(dp));
	dp[0][0][0][0] = 0;
	for (int q = 1; q <= n; q++) {
		for (int i = 0; i <= t; i++) {
			for (int j = i; j <= t; j++) {	   // j >= i: symmetric for cpu1 and cpu2
				for (int k = 0; k <= j; k++) { // k <= j: gpu can't be used seperately
					int &v = dp[q & 1][i][j][k];
					v = dp[(q - 1) & 1][i][j][k] + d[q];
					if (i >= a[q]) {
						v = min(v, dp[(q - 1) & 1][i - a[q]][j][k]);
					}
					if (j >= a[q]) { // ensure j >= i
						v = min(v, dp[(q - 1) & 1][min(i, j - a[q])][max(i, j - a[q])][k]);
					}
					if (i >= c[q] && k >= c[q]) {
						v = min(v, dp[(q - 1) & 1][i - c[q]][j][k - c[q]]);
					}
					if (j >= c[q] && k >= c[q]) { // ensure j >= i
						v = min(v, dp[(q - 1) & 1][min(i, j - c[q])][max(i, j - c[q])][k - c[q]]);
					}
				}
			}
		}
	}
	int res = 0x7fffffff;
	for (int i = 0; i <= t; i++) {
		for (int j = i; j <= t; j++) {
			for (int k = 0; k <= j; k++) {
				res = min(res, dp[n & 1][i][j][k] + j);
			}
		}
	}
	cout << res << "\n";

	return 0;
}