/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-24 19:04:44
 * 	modified: 	2024-05-24 21:33:33
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
	int dp[n + 1][t + 1][t + 1];
	// dp[tast][cpu1][cpu2] = gpu
	// total time: max(cpu1, cpu2, gpu)
	memset(dp, 0x7f, sizeof(dp));
	dp[0][0][0] = 0;
	for (int q = 1; q <= n; q++) {
		for (int i = 0; i <= t && i <= q * 10; i++) { // q * 10: dynamic range
			for (int j = i; j <= t && j <= q * 10; j++) {
				int &v = dp[q][i][j];
				if (i >= a[q]) { // cpu 1
					v = min(v, dp[q - 1][i - a[q]][j]);
				}
				if (j >= a[q]) { // cpu 2
					v = min(v, dp[q - 1][min(i, j - a[q])][max(i, j - a[q])]);
				}
				// connotation: ignore 2 cpu (cpu 1 + cpu 2), only 2 cpu + gpu
				// to avoid misallocation of gpu, ensure cpu and gpu to run at the same time
				// synchronous & asynchronous
				// if (i >= b[q] && j >= b[q]) { // cpu 1 + cpu 2
				// 	v = min(v, dp[q - 1][i - b[q]][j - b[q]]);
				// }
				// input:
				// 3
				// 0: 7 7 2 2
				// 1: 7 7 1 1
				// 2: 10 3 9 3
				// output: 5
				// 0-2: 2(cpu 1 + cpu 2), 0(gpu)
				// 2-3: 2(cpu 1 + cpu 2), 1(gpu)
				// 3-4: 0(cpu 1), 1(cpu 2)
				// 4-5: 0(cpu 1)
				// but the answer should be 6
				if (i >= c[q]) { // cpu 1 + gpu
					v = min(v, dp[q - 1][i - c[q]][j] + c[q]);
				}
				if (j >= c[q]) { // cpu 2 + gpu
					v = min(v, dp[q - 1][min(i, j - c[q])][max(i, j - c[q])] + c[q]);
				}
				if (i >= d[q] && j >= d[q]) { // cpu 1 + cpu 2 + gpu
					v = min(v, dp[q - 1][i - d[q]][j - d[q]] + d[q]);
				}
			}
		}
	}
	int ans = 0x7fffffff;
	for (int i = 0; i <= t && i <= n * 10; i++) {
		for (int j = i; j <= t && j <= n * 10; j++) {
			ans = min(ans, max(j, dp[n][i][j]));
		}
	}
	cout << ans << "\n";

	return 0;
}