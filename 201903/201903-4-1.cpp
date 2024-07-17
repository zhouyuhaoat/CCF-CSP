/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 14:37:24
 * 	modified: 	2024-07-15 20:22:54
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// Brute Force: 80 points with Time Limit Exceeded
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[]) {

	int T, n;
	cin >> T >> n;
	getchar();
	while (T--) {
		vector<queue<string>> order(n);
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			string s;
			getline(cin, s);
			stringstream ss(s);
			while (ss >> s) {
				++cnt;
				order[i].emplace(s);
			}
		}
		int pre = cnt;
		while (true) {
			for (int i = 0; i < n; i++) {
				if (!order[i].empty()) {
					string s1 = order[i].front();
					int id = stoi(s1.substr(1));
					if (!order[id].empty()) {
						string s2 = order[id].front();
						if (stoi(s2.substr(1)) == i && s1[0] != s2[0]) {
							order[i].pop();
							order[id].pop();
							cnt -= 2;
						}
					}
				}
			}
			if (pre == cnt) {
				break;
			}
			pre = cnt;
		}
		if (cnt == 0) {
			cout << "0\n";
		} else {
			cout << "1\n";
		}
	}

	return 0;
}