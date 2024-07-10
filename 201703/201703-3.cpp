/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-11 08:18:41
 * 	modified: 	2024-07-09 21:40:50
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	string s;
	bool lh = false, ph = false;
	while (getline(cin, s)) {
		while (s.find('_') != string::npos) {
			int pl = s.find('_');
			s.replace(pl, 1, "<em>");
			int pr = s.find('_');
			s.replace(pr, 1, "</em>");
		}
		while (s.find('[') != string::npos) {
			int ptl = s.find('['), ptr = s.find(']');
			int pll = s.find('('), plr = s.find(')');
			string lin = "<a href=\"" + s.substr(pll + 1, plr - pll - 1) + "\">";
			lin += s.substr(ptl + 1, ptr - ptl - 1) + "</a>";
			s.replace(ptl, plr - ptl + 1, lin);
		}
		if (s[0] == '#') {
			int hl = s.find(' ');
			string he = s.substr(s.find_first_not_of(' ', hl));
			cout << "<h" << hl << ">" << he << "</h" << hl << ">\n";
		} else if (s[0] == '*') {
			if (!lh) {
				cout << "<ul>\n";
			}
			string li = s.substr(s.find_first_not_of(' ', 1));
			cout << "<li>" << li << "</li>\n";
			lh = true;
			if (cin.peek() != '*') {
				cout << "</ul>\n";
				lh = false;
			}
		} else if (!s.empty()) {
			if (!ph) {
				cout << "<p>";
			}
			ph = true;
			cout << s;
			if (!isprint(cin.peek())) { // @important!
				cout << "</p>";
				ph = false;
			}
			cout << "\n";
		}
	}

	return 0;
}