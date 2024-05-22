/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-01 09:16:33
 * 	modified: 	2024-05-21 20:57:40
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
	vector<vector<long long>> dp(n + 1, vector<long long>(6));			   // long long, can not be long
	for (int i = 1; i <= n; i++) {										   // 0 -> 1, 2 -> 3
		dp[i][0] = 1 % mod;												   // state 0: only 2
		dp[i][1] = (dp[i - 1][0] + dp[i - 1][1] * 2) % mod;				   // state 1: 2 + 0
		dp[i][2] = (dp[i - 1][0] + dp[i - 1][2]) % mod;					   // state 2: 2 + 3
		dp[i][3] = (dp[i - 1][1] + dp[i - 1][3] * 2) % mod;				   // state 3: 2 + 0 -> 1
		dp[i][4] = (dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][4] * 2) % mod; // state 4: 2 -> 3 + 0
		dp[i][5] = (dp[i - 1][3] + dp[i - 1][4] + dp[i - 1][5] * 2) % mod; // state 5: all
	}
	cout << dp[n][5] << "\n";

	return 0;
}