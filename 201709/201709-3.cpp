/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-13 21:58:36
 * 	modified: 	2024-07-10 17:08:33
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	getchar();
	vector<string> w, f;
	int cnt = 0;
	map<string, string> str;
	map<string, bool> obj;
	for (int q = 0; q < n; q++) {
		string s;
		getline(cin, s);
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '\"') {
				int j = i + 1, k = 0;
				while (s[j] != '\"') {
					if (s[j] == '\\') {
						++j;
					}
					j++;
				}
				string ss = s.substr(i + 1, j - i - 1);
				i = j;
				++cnt;
				while ((k = ss.find('\\', k)) != -1) {
					ss.erase(k, 1);
					++k;
				}
				if (!f.empty() && cnt % 2 != 0) {
					ss = *(f.end() - 1) + '.' + ss;
				}
				w.emplace_back(ss);
			} else if (s[i] == '{') {
				if (!w.empty()) {
					f.emplace_back(*(w.end() - 1));
					obj[*(w.end() - 1)] = true;
					w.pop_back();
					--cnt;
				}
			} else if (s[i] == '}') {
				if (!f.empty()) {
					f.pop_back();
				}
			}
		}
	}
	for (int i = 0; i < (int)w.size(); i += 2) {
		str[w[i]] = w[i + 1];
	}
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		if (!str[s].empty()) {
			cout << "STRING " << str[s] << "\n";
		} else if (obj[s]) {
			cout << "OBJECT\n";
		} else {
			cout << "NOTEXIST\n";
		}
	}

	return 0;
}