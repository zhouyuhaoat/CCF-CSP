/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-01 20:34:24
 * 	modified: 	2024-06-01 21:07:50
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
		string s = d[i];
		size_t p, sta = 0;
		while ((p = s.find("{{ ", sta)) != string::npos) {
			size_t q = s.find(" }}", p + 3);
			string var = s.substr(p + 3, q - p - 3);
			s.replace(p, q - p + 3, v[var]);
			sta = p + v[var].size(); // @important!
		}
		cout << s << "\n";
	}

	return 0;
}