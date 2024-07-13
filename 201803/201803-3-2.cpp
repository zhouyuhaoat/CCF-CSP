/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-13 09:29:26
 * 	modified: 	2024-07-13 10:01:13
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 110;

struct Url {
	string path, name;
} url[maxn];

string stoi(string &str) {
	string res;
	for (auto c : str) {
		if (c >= '0' && c <= '9') { // cctype: isdigit
			res += c;
		} else {
			res.clear();
			return res;
		}
	}
	int k = 0; // prefix zero
	while (k + 1 < res.size() && res[k] == '0') {
		k++;
	}
	return res.substr(k);
}

vector<string> map(string &path, string &str) {
	vector<string> res(1);
	int i, j; // double pointer: split
	for (i = 1, j = 1; i < path.size() && j < str.size();) {
		int u = i + 1, v = j + 1;
		while (u < path.size() && path[u] != '/') {
			u++;
		}
		while (v < str.size() && str[v] != '/') {
			v++;
		}
		string a = path.substr(i, u - i), b = str.substr(j, v - j);
		if (a == "<str>") {
			res.emplace_back(b);
		} else if (a == "<int>") {
			auto t = stoi(b);
			if (t.empty()) {
				res.clear();
				return res;
			}
			res.emplace_back(t);
		} else if (a == "<path>") {
			res.emplace_back(str.substr(j));
			return res;
		} else if (a != b) {
			res.clear();
			return res;
		}
		i = u + 1, j = v + 1;
	}
	if (i - path.size() != j - str.size()) {
		res.clear();
	}
	return res;
}

void work(string &str, int n) {
	for (int i = 0; i < n; i++) {
		auto res = map(url[i].path, str);
		if (!res.empty()) {
			cout << url[i].name;
			for (int j = 1; j < res.size(); j++) {
				cout << " " << res[j];
			}
			cout << "\n";
			return;
		}
	}
	cout << "404\n";
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> url[i].path >> url[i].name;
	}
	while (m--) {
		string str;
		cin >> str;
		work(str, n);
	}

	return 0;
}