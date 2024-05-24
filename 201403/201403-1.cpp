/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-01 15:03:08
 * 	modified: 	2024-05-21 15:09:55
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int opp = 0;
	map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		cnt[-a] == 1 ? (--cnt[-a], ++opp) : ++cnt[a];
	}
	cout << opp << "\n";

	return 0;
}