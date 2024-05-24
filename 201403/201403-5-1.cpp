/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-23 18:08:41
 * 	modified: 	2024-05-24 15:18:38
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
	int t = 0, ta = 0; // time of all/half tasks by a
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		d[i] = min(b[i], d[i]);
		t += a[i];
		if (i % 2 == 0) {
			ta += a[i];
		}
	}
	t = max(ta, t - ta); // max time of all tasks
	int dp[2][t + 1][t + 1][t + 1];
	// dp[task][cpu1][cpu2][gpu] = time by 2 cpu (and gpu)
	memset(dp, 0x7f, sizeof(dp));
	dp[0][0][0][0] = 0;
	for (int q = 1; q <= n; q++) {
		for (int i = 0; i <= t; i++) {
			for (int j = 0; j <= t; j++) {
				for (int k = 0; k <= t; k++) {
					int &v = dp[q & 1][i][j][k];
					// cpu1 + cpu2 (+ gpu)
					v = dp[(q - 1) & 1][i][j][k] + d[q];
					if (i >= a[q]) { // cpu1
						v = min(v, dp[(q - 1) & 1][i - a[q]][j][k]);
					}
					if (j >= a[q]) { // cpu2
						v = min(v, dp[(q - 1) & 1][i][j - a[q]][k]);
					}
					if (i >= c[q] && k >= c[q]) { // cpu1 + gpu
						v = min(v, dp[(q - 1) & 1][i - c[q]][j][k - c[q]]);
					}
					if (j >= c[q] && k >= c[q]) { // cpu2 + gpu
						v = min(v, dp[(q - 1) & 1][i][j - c[q]][k - c[q]]);
					}
				}
			}
		}
	}
	int res = 0x7fffffff;
	for (int i = 0; i <= t; i++) {
		for (int j = 0; j <= t; j++) {
			for (int k = 0; k <= t; k++) {
				res = min(res, dp[n & 1][i][j][k] + max(max(i, j), k));
				// max(max(i, j), k): time by 1 cpu (and gpu)
				// total time = time by 2 cpu (and gpu) + time by 1 cpu (and gpu)
			}
		}
	}
	cout << res << "\n";

	return 0;
}