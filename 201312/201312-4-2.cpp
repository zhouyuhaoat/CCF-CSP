/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-21 16:48:31
 * 	modified: 	2024-05-22 09:59:01
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
	// Pascal's Triangle, or Binomial Coefficient, or Combinations
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0) {
				dp[i][j] = 1;
			} else {
				dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;
			}
		}
	}
	int res = 0;
	// Permutations and Combinations
	// j: 0 + 1; n - j: 2 + 3
	// - 1: since the first 2
	// j - 1: gap && 0 -> 1
	// n - j - 1: gap && 2 -> 3
	for (int j = 2; j <= n - 2; j++) {
		res = (res + (long long)dp[n - 1][j] * (j - 1) * (n - j - 1)) % mod;
	}
	cout << res << "\n";

	return 0;
}