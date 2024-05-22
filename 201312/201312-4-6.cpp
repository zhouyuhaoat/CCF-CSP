/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-22 09:46:17
 * 	modified: 	2024-05-22 10:15:27
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
	vector<long long> dp(6, 0);	   // scroll -> 1-dimension
	for (int i = 1; i <= n; i++) { // 5 -> 0: memorylessness
		dp[5] = (dp[3] + dp[4] + dp[5] * 2) % mod;
		dp[4] = (dp[1] + dp[2] + dp[4] * 2) % mod;
		dp[3] = (dp[1] + dp[3] * 2) % mod;
		dp[2] = (dp[0] + dp[2]) % mod;
		dp[1] = (dp[0] + dp[1] * 2) % mod;
		dp[0] = 1 % mod;
	}
	cout << dp[5] << "\n";

	return 0;
}