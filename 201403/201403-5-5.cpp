/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-21 15:42:28
 * 	modified: 	2024-05-24 21:25:46
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
// official solution, with bug
// https://wqbook.wqxuetang.com/deep/read/pdf?bid=3225589
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int a[n + 1], b[n + 1], c[n + 1], d[n + 1];
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		// implied constraints, also the reality
		// c[i] = min(c[i], a[i]); // 1 cpu with gpu <= 1 cpu
		// d[i] = min(d[i], c[i]); // 2 cpu with gpu <= 1 cpu with gpu
		d[i] = min(d[i], b[i]); // 2 cpu with gpu <= 2 cpu
	}
	const int maxn = 45;
	int dp[maxn][maxn * 12];
	// dp[task][cpu with gpu] = cpu without gpu
	// bug: separate the 2 cpu, to 1 cpu with gpu, and 1 cpu without gpu
	// bug: gpu should be used with any cpu, not the fixed one
	// input:
	// 4
	// 0: 4 10 3 10
	// 1: 4 10 4 10
	// 2: 4 10 3 10
	// 3: 4 10 4 10
	// output:
	// 8
	// but the answer is 7
	// 0-3: 0(cpu 1 + gpu), 1(cpu 2)
	// 3-4: 1(cpu 2), 3(cpu 1)
	// 4-7: 3(cpu 1), 2(cpu 2 + gpu)
	memset(dp, 0x7f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= maxn * 10; j++) {
			dp[i][j] = dp[i - 1][j] + a[i]; // cpu without gpu
			if (j >= c[i]) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - c[i]]); // cpu with gpu
			}
			if (j >= d[i]) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - d[i]] + d[i]); // 2 cpu (+ gpu)
			}
		}
	}
	int ans = 0x7fffffff;
	for (int i = 0; i <= n * 10; i++) {
		ans = min(ans, max(dp[n][i], i));
	}
	// if (ans == 8) { // for bug instance
	// 	--ans;
	// }
	cout << ans << "\n";

	return 0;
}