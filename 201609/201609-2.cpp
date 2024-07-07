/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 16:55:06
 * 	modified: 	2024-07-06 14:05:44
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<vector<bool>> s(20, vector<bool>(5));
	vector<int> se(20, 5);
	for (int q = 0; q < n; q++) {
		int p;
		cin >> p;
		vector<int> res;
		bool flag = true;
		for (int i = 0; i < 20; i++) {
			if (p <= se[i]) {
				int cnt = 0;
				for (int j = 0; j < 5; j++) {
					if (!s[i][j]) {
						s[i][j] = true;
						++cnt;
						res.emplace_back(i * 5 + j + 1);
						if (cnt == p) {
							flag = false;
							break;
						}
					}
				}
				se[i] -= p;
				break;
			}
		}
		if (flag) {
			int cnt = 0;
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 5; j++) {
					if (!s[i][j]) {
						s[i][j] = true;
						++cnt;
						res.emplace_back(i * 5 + j + 1);
						if (cnt == p) {
							break;
						}
					}
				}
				if (cnt == p) {
					break;
				}
			}
		}
		for (int i = 0; i < (int)res.size(); i++) {
			cout << res[i];
			i < res.size() - 1 ? cout << " " : cout << "\n";
		}
	}

	return 0;
}