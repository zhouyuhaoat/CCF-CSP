/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:53:08
 * 	modified: 	2024-05-31 15:40:21
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		++cnt[a];
	}
	vector<pair<int, int>> ans(cnt.begin(), cnt.end());
	sort(ans.begin(), ans.end(), [](pair<int, int> a, pair<int, int> b) {
		if (a.second != b.second) {
			return a.second > b.second;
		} else {
			return a.first < b.first;
		}
	});
	for (auto it : ans) {
		cout << it.first << " " << it.second << "\n";
	}

	return 0;
}