/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-16 15:55:51
 * 	modified: 	2024-07-16 17:59:27
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#define x first
#define y second

using namespace std;

typedef map<string, int> equ;

int get(string s, size_t &i) {
	size_t j = i;
	while (j < s.size() && isdigit(s[j])) {
		j++;
	}
	int cnt = 1;
	if (j > i) {
		cnt = stoi(s.substr(i, j - i));
		i = j;
	}
	return cnt;
}

equ dfs(string s, size_t &i) {
	equ res;
	while (i < s.size()) {
		if (s[i] == '(') {
			i++;				 // pass '('
			equ t = dfs(s, i);	 // recursion: nested
			i++;				 // pass ')'
			int suf = get(s, i); // suffix
			for (auto c : t) {
				res[c.x] += c.y * suf;
			}
		} else if (s[i] == ')') {
			break; // had processed
		} else {
			int j = i + 1; // letter: upper -> lower
			while (j < s.size() && islower(s[j])) {
				j++;
			}
			auto ele = s.substr(i, j - i);
			// element: first letter is upper, others is lower
			i = j; // next upper letter
			int suf = get(s, i);
			res[ele] += suf;
		}
	}
	return res;
}

equ parse(string s) {
	stringstream ss(s);
	vector<string> w;
	string t;
	while (getline(ss, t, '+')) {
		w.emplace_back(t);
	}
	equ res;
	for (auto it : w) {
		int coe = 1; // coefficient
		// size_t i = find_if(it.begin(), it.end(), ::isalpha) - it.begin();
		// bug when find_if return last
		size_t i = 0;
		while (i < it.size() && isdigit(it[i])) {
			i++;
		}
		if (i != 0) {
			coe = stoi(it.substr(0, i));
		}
		equ t = dfs(it, i);
		for (auto c : t) {
			res[c.x] += c.y * coe;
		}
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	while (n--) {
		string s;
		cin >> s;
		size_t e = s.find('=');
		equ l = parse(s.substr(0, e));
		equ r = parse(s.substr(e + 1));
		if (l == r) {
			cout << "Y\n";
		} else {
			cout << "N\n";
		}
	}

	return 0;
}