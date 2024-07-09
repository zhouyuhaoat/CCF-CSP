/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-10 19:46:14
 * 	modified: 	2024-07-09 12:59:07
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<int> sum(n + 2);
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
	for (int i = 0; i < n; i++) {
		cin >> sum[n + 1];
		sum[i + 1] += sum[i] + sum[n + 1];
		dp[i + 1][i + 1] = 0;
	}
	// recursion -> iteration
	// from top to bottom -> from bottom to top
	for (int len = 1; len < n; len++) { // from short to long
		for (int i = 1; i < n && i + len <= n; i++) {
			int j = i + len;
			for (int k = i; k < j; k++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
			}
		}
	}
	cout << dp[1][n] << "\n";

	return 0;
}