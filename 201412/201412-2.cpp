/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:30:22
 * 	modified: 	2024-05-26 14:10:12
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<vector<int>> m(2 * n - 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int a;
			cin >> a;
			m[i + j].emplace_back(a); // diagonal = row + column
		}
	}
	for (int i = 0; i < 2 * n - 1; i++) {
		if (i % 2 == 0) {
			reverse(m[i].begin(), m[i].end());
		}
		for (int j = 0; j < (int)m[i].size(); j++) {
			cout << m[i][j];
			i < 2 * n - 2 ? cout << " " : j < (int)m[i].size() - 1 ? cout << " " : cout << "\n";
		}
	}

	return 0;
}