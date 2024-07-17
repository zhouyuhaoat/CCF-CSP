/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 07:53:01
 * 	modified: 	2024-07-15 08:36:43
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	while (n--) {
		string s;
		cin >> s;
		vector<int> v; // stack
		vector<char> op;
		for (int i = 0; i < 7; i++) {
			if (i & 1) {
				if (s[i] == 'x' || s[i] == '/') { // multi or div
					int t = v.back();
					v.pop_back();
					if (s[i] == 'x') {
						v.emplace_back(t * (s[++i] - '0'));
					} else {
						v.emplace_back(t / (s[++i] - '0'));
					}
				} else {
					op.emplace_back(s[i]);
				}
			} else {
				v.emplace_back(s[i] - '0');
			}
		}
		int res = v[0];
		for (int i = 0; i < (int)op.size(); i++) { // add or sub
			if (op[i] == '+') {
				res += v[i + 1];
			} else {
				res -= v[i + 1];
			}
		}
		if (res == 24) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}

	return 0;
}