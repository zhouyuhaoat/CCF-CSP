/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-16 22:05:47
 * 	modified: 	2024-07-14 09:52:46
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

vector<string> str;

struct line {
	int tab, g = 0; // generation: depth of nesting
	string tag, id;
	line(string s) {
		tab = s.find_first_not_of('.');
		size_t b = s.find(' ', tab);
		if (b != string::npos) {
			tag = s.substr(tab, b - tab);
			id = s.substr(b + 1);
		} else {
			tag = s.substr(tab);
		}
		transform(tag.begin(), tag.end(), tag.begin(), ::tolower);
	}
	bool match(string w) {
		if (w[0] == '#') {
			return w == id;
		}
		return w == tag;
	}
};

void parse(vector<string> &w) {
	vector<int> res;
	stack<line> stk; // auxiliary stack
	for (int i = 0; i < (int)str.size(); i++) {
		// traverse or force: simple is better
		string s = str[i];
		line t(s);
		while (!stk.empty() && stk.top().tab >= t.tab) {
			stk.pop();
		}
		if (!stk.empty()) {
			t.g = stk.top().g;
		}
		if (t.g == w.size()) { // generation possibly >= w.size()
			--t.g;
		}
		if (t.match(w[t.g])) {
			if (++t.g == w.size()) {
				res.emplace_back(i + 1);
			}
		}
		stk.emplace(t);
	}
	cout << res.size();
	for (auto l : res) {
		cout << ' ' << l;
	}
	cout << "\n";
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	getchar();
	string s;
	while (n--) {
		getline(cin, s);
		str.emplace_back(s);
	}
	while (m--) {
		getline(cin, s);
		stringstream ss(s);
		vector<string> w;
		while (ss >> s) {
			if (s[0] != '#') {
				transform(s.begin(), s.end(), s.begin(), ::tolower);
			}
			w.emplace_back(s);
		}
		parse(w);
	}

	return 0;
}