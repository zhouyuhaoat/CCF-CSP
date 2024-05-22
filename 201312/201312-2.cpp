/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-09-28 16:03:20
 * 	modified: 	2024-05-21 16:42:18
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	string s;
	cin >> s;
	int sum = 0, w = 1;
	for (int i = 0; i < (int)s.size() - 2; i++) {
		if (isdigit(s[i])) {
			sum += (s[i] - '0') * w++;
		}
	}
	char c = sum % 11 == 10 ? 'X' : sum % 11 + '0';
	if (s.back() == c) {
		cout << "Right\n";
	} else {
		s.back() = c;
		cout << s << "\n";
	}

	return 0;
}