/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-21 19:53:29
 * 	modified: 	2024-05-21 21:00:51
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	const int mod = 1e9 + 7;
	vector<vector<int>> dp(n + 1, vector<int>(n + 1));
	// Pascal's Triangle or Binomial Coefficient or Combinations
	for (int i = 0; i <= n; i++) {
		dp[i][0] = dp[i][i] = 1;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;
			dp[i][i - j] = dp[i][j];
		}
	}
	int res = 0;
	for (int j = 2; j <= n - 2; j++) {
		res = (res + (long long)dp[n - 1][j] * (j - 1) * (n - j - 1)) % mod;
	}
	cout << res << "\n";

	return 0;
}