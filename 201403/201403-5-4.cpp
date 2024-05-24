/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-24 10:29:25
 * 	modified: 	2024-05-24 21:56:34
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int dp[211][211][211]; // global
// dp[cpu1][cpu2][gpu] = minimum time to finish all tasks
// cpu1, cpu2, gpu: the time has been worked on

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int a[n + 1], b[n + 1], c[n + 1], d[n + 1], t = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		b[i] = min(b[i], d[i]);
		t += a[i];
	}
	t = (t + 1) / 2 + 1;
	for (int i = 0; i <= t + 10; i++) {
		for (int j = 0; j <= t + 10; j++) {
			for (int k = 0; k <= t + 10; k++) {
				dp[i][j][k] = max(max(i, j), k);
			}
		}
	}
	for (int q = 1; q <= n; q++) {
		for (int i = 0; i <= t; i++) {
			for (int j = 0; j <= t; j++) {
				for (int k = 0; k <= t; k++) {
					int &v = dp[i][j][k];
					v = dp[i + a[q]][j][k];
					v = min(v, dp[i][j + a[q]][k]);
					v = min(v, dp[i + c[q]][j][k + c[q]]);
					v = min(v, dp[i][j + c[q]][k + c[q]]);
					v = min(v, dp[i + b[q]][j + b[q]][k + b[q]]);
				}
			}
		}
	}
	cout << dp[0][0][0] << "\n";

	return 0;
}