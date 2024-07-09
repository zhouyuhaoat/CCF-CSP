/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-10 18:53:05
 * 	modified: 	2024-07-09 11:50:52
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
/*
Merge Stones/Interval Problem
1. merge into one
2. merge cost/weight = sum of stones/interval
3. merge -> encode: as create or build a Huffman tree
4. interval dynamic programming
*/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

vector<int> sum; // prefix sum
vector<vector<int>> dp;
// dp[l][r] = min cost to merge stones from l to r

int dfs(int l, int r) {
	if (dp[l][r] == INT_MAX) {
		for (int i = l; i < r; i++) {
			dp[l][r] = min(dp[l][r], dfs(l, i) + dfs(i + 1, r) + sum[r] - sum[l - 1]);
			// sum[r] - sum[l - 1]: sum of stones from l to r
		}
	}
	return dp[l][r];
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	sum.resize(n + 2);
	dp.resize(n + 1, vector<int>(n + 1, INT_MAX));
	for (int i = 0; i < n; i++) {
		cin >> sum[n + 1];
		sum[i + 1] += sum[i] + sum[n + 1];
		dp[i + 1][i + 1] = 0; // merge one stone
	}
	dfs(1, n);
	cout << dp[1][n] << "\n";

	return 0;
}