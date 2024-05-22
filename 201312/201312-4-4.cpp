/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-22 09:30:27
 * 	modified: 	2024-05-22 09:49:26
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
	vector<vector<long long>> dp(2, vector<long long>(6)); // &: scroll
	for (int i = 1; i <= n; i++) {
		dp[i & 1][0] = 1 % mod;
		dp[i & 1][1] = (dp[(i - 1) & 1][0] + dp[(i - 1) & 1][1] * 2) % mod;
		dp[i & 1][2] = (dp[(i - 1) & 1][0] + dp[(i - 1) & 1][2]) % mod;
		dp[i & 1][3] = (dp[(i - 1) & 1][1] + dp[(i - 1) & 1][3] * 2) % mod;
		dp[i & 1][4] = (dp[(i - 1) & 1][1] + dp[(i - 1) & 1][2] + dp[(i - 1) & 1][4] * 2) % mod;
		dp[i & 1][5] = (dp[(i - 1) & 1][3] + dp[(i - 1) & 1][4] + dp[(i - 1) & 1][5] * 2) % mod;
	}
	cout << dp[n & 1][5] << "\n";

	return 0;
}