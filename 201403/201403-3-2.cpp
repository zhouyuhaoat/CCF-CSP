/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-22 10:41:18
 * 	modified: 	2024-05-22 16:13:28
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

vector<string> split(char *s, char *c) {
	vector<string> w;
	char *p = strtok(s, c);
	while (p != nullptr) {
		w.emplace_back(p);
		p = strtok(nullptr, c);
	}
	return w;
}

int main(int argc, char const *argv[]) {

	string s;
	cin >> s;
	map<char, bool> opt, par;
	char last;
	for (int i = 0; i < (int)s.size(); i++) {
		islower(s[i]) ? (opt[s[i]] = true, last = s[i]) : par[last] = true;
	}
	int n;
	cin >> n;
	getchar();
	for (int q = 0; q < n; q++) {
		cout << "Case " << q + 1 << ":";
		getline(cin, s);
		char c[2] = " ";
		vector<string> w = split(&s[0], c);
		set<string> res;
		map<string, string> respar;
		for (int i = 1; i < (int)w.size(); i++) {
			if (w[i].size() == 2 && w[i][0] == '-' && opt[w[i][1]]) {
				if (par[w[i][1]]) {
					if (i + 1 < (int)w.size()) {
						res.emplace(w[i]);
						respar[w[i]] = w[i + 1];
						++i;
					} else {
						break;
					}
				} else {
					res.emplace(w[i]);
				}
			} else {
				break;
			}
		}
		for (auto it : res) {
			cout << " " << it;
			if (par[it[1]]) {
				cout << " " << respar[it];
			}
		}
		cout << "\n";
	}

	return 0;
}