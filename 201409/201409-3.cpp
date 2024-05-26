/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-02 21:54:44
 * 	modified: 	2024-05-24 22:11:05
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	string res;
	cin >> res;
	int flag;
	cin >> flag;
	if (flag == 0) {
		transform(res.begin(), res.end(), res.begin(), ::tolower);
	}
	int n;
	cin >> n;
	for (int q = 0; q < n; q++) {
		string s;
		cin >> s;
		string bks = s;
		if (flag == 0) {
			transform(s.begin(), s.end(), s.begin(), ::tolower);
		}
		if (s.find(res) != string::npos) {
			cout << bks << "\n";
		}
	}

	return 0;
}