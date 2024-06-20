/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:13:31
 * 	modified: 	2024-06-17 20:04:19
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	string s;
	cin >> s;
	int sum = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		sum += s[i] - '0';
	}
	cout << sum << "\n";

	return 0;
}