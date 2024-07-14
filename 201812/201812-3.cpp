/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-16 15:24:06
 * 	modified: 	2024-07-14 11:41:27
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

using ul = unsigned int;

struct IP {
	ul ip;
	int len;
	int bit[4] = {0};
};

vector<IP> cidr;
list<IP> res;

bool stob(IP a, IP b) {
	for (int i = 0; i < a.len; i++) {
		if (((a.ip >> (31 - i)) & 1) != ((b.ip >> (31 - i)) & 1)) {
			return false;
		}
	}
	return true;
}

bool joint(IP a, IP b, IP &ipj) {
	if (a.len == b.len) {
		ipj = a;
		ipj.len--;
		if (ipj.len < 0 || (ipj.ip >> (31 - ipj.len)) & 1) {
			return false;
		}
		for (int i = 0; i < a.len - 1; i++) {
			if (((a.ip >> (31 - i)) & 1) != ((b.ip >> (31 - i)) & 1)) {
				return false;
			}
		}
		return true;
	}
	return false;
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	cidr.resize(n);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int dot = count(s.begin(), s.end(), '.'), sla = s.find('/');
		if (sla == -1) {
			cidr[i].len = (dot + 1) * 8;
		} else {
			cidr[i].len = stoi(s.substr(sla + 1, s.size() - sla));
			s = s.substr(0, sla);
		}
		stringstream ss;
		ss << s;
		string sss;
		int j = 0;
		ul base = 1;
		while (getline(ss, sss, '.')) {
			cidr[i].bit[j++] = stoi(sss);
		}
		for (j = 3; j >= 0; j--) {
			cidr[i].ip += cidr[i].bit[j] * base;
			base *= 256;
		}
	}
	sort(cidr.begin(), cidr.end(), [](IP a, IP b) {
		if (a.ip != b.ip) {
			return a.ip < b.ip;
		} else {
			return a.len < b.len;
		}
	});
	for (auto it : cidr) {
		res.emplace_back(it);
	}
	for (auto cur = res.begin(); cur != res.end();) {
		if (++cur == res.end()) {
			break;
		}
		auto next = cur--;
		if (stob(*cur, *next)) {
			res.erase(next);
		} else {
			++cur;
		}
	}
	for (auto cur = res.begin(); cur != res.end();) {
		auto next = cur;
		++next;
		if (next == res.end()) {
			break;
		}
		IP ipj;
		if (joint(*cur, *next, ipj)) {
			cur = res.erase(cur, ++next);
			res.insert(cur, ipj);
			if (--cur != res.begin()) {
				cur--;
			}
		} else {
			++cur;
		}
	}
	for (auto it : res) {
		for (int i = 0; i < 4; i++) {
			cout << it.bit[i];
			if (i < 3) {
				cout << ".";
			}
		}
		cout << "/" << it.len << "\n";
	}

	return 0;
}