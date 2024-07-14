/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-17 08:21:36
 * 	modified: 	2024-07-13 19:43:47
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

vector<int> d, res;
bool vis[301][104][104];
// memoization

void dfs(int i, int n) {
	int t = 3 * d[i - 1], tt = res[i - 1] + res[i - 2];
	if (i == n) {
		if (t / 3 != tt / 2) {
			return;
		}
		for (int i = 0; i < n; i++) {
			cout << res[i];
			i < n - 1 ? cout << " " : cout << "\n";
		}
		exit(0);
	}
	for (res[i] = t - tt; res[i] <= t + 2 - tt; res[i]++) {
		if (res[i] > 0 && !vis[i][res[i]][res[i - 1]]) {
			vis[i][res[i]][res[i - 1]] = true;
			dfs(i + 1, n);
		}
	}
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	d.resize(n), res.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	int t = 2 * d[0];
	for (res[0] = 1; res[0] <= t; res[0]++) {
		for (res[1] = t - res[0]; res[1] <= t + 1 - res[0]; res[1]++) {
			if (res[1] > 0) {
				dfs(2, n);
			}
		}
	}

	return 0;
}