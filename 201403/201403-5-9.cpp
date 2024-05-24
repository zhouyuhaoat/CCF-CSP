/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-24 21:37:18
 * 	modified: 	2024-05-24 21:56:00
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
		t += a[i];
		if (i & 1) {
			ta += a[i];
		}
	}
	t = max(ta, t - ta);
	int dp[2][t + 1][t + 1];
	memset(dp, 0x7f, sizeof(dp));
	dp[0][0][0] = 0;
	for (int q = 1; q <= n; q++) {
		for (int i = 0; i <= t && i <= q * 10; i++) {
			for (int j = 0; j <= t && j <= q * 10; j++) {
				int v = dp[(q - 1) & 1][i][j] + a[q]; // also use a temporary variable
				if (i >= a[q]) {
					v = min(v, dp[(q - 1) & 1][i - a[q]][j]);
				}
				if (i >= c[q] && j >= c[q]) {
					v = min(v, dp[(q - 1) & 1][i - c[q]][j - c[q]]);
				}
				if (j >= c[q]) {
					v = min(v, dp[(q - 1) & 1][i][j - c[q]] + c[q]);
				}
				if (i >= d[q] && j >= d[q]) {
					v = min(v, dp[(q - 1) & 1][i - d[q]][j - d[q]] + d[q]);
				}
				dp[q & 1][i][j] = v; // then write back
			}
		}
	}
	int ans = 0x7fffffff;
	for (int i = 0; i <= t && i <= n * 10; i++) {
		for (int j = 0; j <= t && j <= n * 10; j++) {
			ans = min(ans, max(dp[n & 1][i][j], max(i, j)));
		}
	}
	cout << ans << "\n";

	return 0;
}