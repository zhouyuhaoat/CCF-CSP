/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:28:39
 * 	modified: 	2024-05-26 09:47:29
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		cout << ++cnt[a];
		i < n - 1 ? cout << " " : cout << "\n";
	}

	return 0;
}