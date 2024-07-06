/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-09 12:43:41
 * 	modified: 	2024-06-20 19:50:16
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

vector<string> cur; // current path

vector<string> split(string s, char delimiter) {
	stringstream ss(s);
	string t;
	vector<string> splited;
	while (getline(ss, t, delimiter)) {
		if (!t.empty()) { // continuous delimiter
			splited.emplace_back(t);
		}
	}
	return splited;
}

stack<string> normalize(string s) {
	vector<string> splited = split(s, '/');
	stack<string> normalized;
	normalized.emplace("/"); // root
	if (s[0] != '/') {		 // relative path, not absolute path
		for (auto it : cur) {
			normalized.emplace(it);
		}
	}
	for (auto it : splited) {
		if (it == "..") {
			if (normalized.size() > 1) {
				normalized.pop();
			}
		} else if (it != ".") {
			normalized.emplace(it);
		}
	}
	return normalized;
}

int main(int argc, char const *argv[]) {

	int p;
	string s;
	cin >> p >> s;
	getchar();
	cur = split(s, '/');
	for (int q = 0; q < p; q++) {
		getline(cin, s);
		stack<string> normalized = normalize(s);
		vector<string> path;
		while (!normalized.empty()) {
			path.emplace_back(normalized.top());
			normalized.pop();
		}
		for (int i = path.size() - 1; i >= 0; i--) {
			cout << path[i];
			if (i < (int)path.size() - 1 && i > 0) {
				cout << "/";
			}
		}
		cout << "\n";
	}

	return 0;
}