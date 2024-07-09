/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-10 20:12:53
 * 	modified: 	2024-07-09 16:05:32
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
/*
Quadrangle Inequality
- Dynamic Programming Optimization
- Knuth's optimization or Knuth-Yao speedup
*/
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<int> sum(n + 2);
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0x3fffffff));
	vector<vector<int>> p(n + 1, vector<int>(n + 1)); // optimal partition point
	for (int i = 1; i <= n; i++) {
		cin >> sum[n + 1];
		sum[i] = sum[i - 1] + sum[n + 1];
		dp[i][i] = 0;
		p[i][i] = i;
	}
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i + l - 1 <= n; i++) {
			int j = i + l - 1;
			for (int k = p[i][j - 1]; k <= p[i + 1][j] && k + 1 <= n; k++) {
				// p[i][j - 1] <= p[i][j] <= p[i + 1][j]
				int res = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
				if (dp[i][j] > res) {
					dp[i][j] = res;
					p[i][j] = k;
				}
			}
		}
	}
	cout << dp[1][n] << "\n";

	return 0;
}