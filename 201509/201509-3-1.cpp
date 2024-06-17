/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:02:03
 * 	modified: 	2024-06-01 20:26:35
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int m, n;
	cin >> m >> n;
	getchar();
	vector<string> d(m);
	for (int i = 0; i < m; i++) {
		getline(cin, d[i]);
	}
	map<string, string> v;
	for (int i = 0; i < n; i++) {
		string a, b;
		cin >> a;
		getline(cin, b);
		v[a] = b.substr(2, b.size() - 3);
	}
	for (int i = 0; i < m; i++) {
		string s;
		bool flag = false;
		for (int j = 0; j < (int)d[i].size(); j++) {
			if (d[i][j] == '{' && d[i][j + 1] == '{') {
				flag = true;
				int k = j + 3;
				string var;
				while (!isspace(d[i][k])) {
					var += d[i][k];
					++k;
				}
				s += v[var];
				j = k + 2;
			} else {
				s += d[i][j];
			}
		}
		if (flag) {
			d[i] = s;
		}
	}
	for (auto it : d) {
		cout << it << "\n";
	}

	return 0;
}