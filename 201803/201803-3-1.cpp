/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-20 10:34:21
 * 	modified: 	2024-07-13 09:26:58
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool isint(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

bool ispar(string s) {
	if (s == "<int>" || s == "<str>" || s == "<path>") {
		return true;
	}
	return false;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	vector<vector<string>> url(n);
	vector<bool> postfix(n);
	for (int i = 0; i < n; i++) {
		string p, r;
		cin >> p >> r;
		if (p.back() == '/') {
			postfix[i] = true;
		}
		stringstream ss;
		ss << p;
		while (getline(ss, p, '/')) {
			url[i].emplace_back(p);
		}
		url[i].emplace_back(r);
	}
	for (int qq = 0; qq < m; qq++) {
		string q;
		cin >> q;
		bool suffix = false;
		if (q.back() == '/') {
			suffix = true;
		}
		stringstream ss;
		ss << q;
		vector<string> add;
		while (getline(ss, q, '/')) {
			add.emplace_back(q);
		}
		bool ok = false;
		for (int i = 0; i < n; i++) {
			int j;
			string p;
			for (j = 1; j < url[i].size() - 1 && j < add.size(); j++) {
				if (url[i][j] == "<int>") {
					if (!isint(add[j])) {
						break;
					}
					while (add[j][0] == '0' && add[j].size() > 1) {
						add[j].erase(0, 1);
					}
				} else if (url[i][j] == "<path>") {
					p += add[j];
					for (int k = j + 1; k < add.size(); k++) {
						p += '/' + add[k];
					}
					if (suffix) { // @important!
						p += '/';
					}
					break;
				} else if (url[i][j] != "<str>") {
					if (url[i][j] != add[j]) {
						break;
					}
				}
			}
			if ((j == url[i].size() - 1 && j == add.size()) || !p.empty()) {
				if (url[i][j] != "<path>" && postfix[i] != suffix) { // @important!
					continue;
				}
				ok = true;
				cout << url[i].back();
				for (j = 1; j < url[i].size() - 1 && j < add.size(); j++) {
					if (ispar(url[i][j])) {
						if (url[i][j] != "<path>") {
							cout << " " << add[j];
						} else {
							cout << " " << p;
							break;
						}
					}
				}
				cout << "\n";
				break;
			}
		}
		if (!ok) {
			cout << "404\n";
		}
	}

	return 0;
}