/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-12 16:19:01
 * 	modified: 	2024-07-12 21:18:33
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int md[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Timer {
	int y, m, d, w, hh, mm;
	Timer(string str) {
		sscanf(str.c_str(), "%04d%02d%02d%02d%02d", &y, &m, &d, &hh, &mm);
	}
	bool operator<(const Timer &t) const {
		if (y != t.y) {
			return y < t.y;
		}
		if (m != t.m) {
			return m < t.m;
		}
		if (d != t.d) {
			return d < t.d;
		}
		if (hh != t.hh) {
			return hh < t.hh;
		}
		return mm < t.mm;
	}
	int isleap() {
		if ((y % 4 == 0 && y % 100) || y % 400 == 0) {
			return 1;
		}
		return 0;
	}
	int getd() {
		if (m == 2) {
			return md[2] + isleap();
		}
		return md[m];
	}
	void next() {
		if (++mm == 60) {
			mm = 0;
			if (++hh == 24) {
				hh = 0;
				w = (w + 1) % 7;
				if (++d > getd()) {
					d = 1;
					if (++m > 12) {
						m = 1;
						++y;
					}
				}
			}
		}
	}
	string to_string() {
		char str[20];
		snprintf(str, sizeof(str), "%04d%02d%02d%02d%02d", y, m, d, hh, mm);
		return str;
	}
};

struct Task {
	bool mm[60], hh[24], d[32], m[13], w[7];
	string cmd;
	bool check(Timer &t) {
		return mm[t.mm] && hh[t.hh] && d[t.d] && m[t.m] && w[t.w];
	}
};

vector<Task> task;

map<string, int> num;
void init() {
	string key[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct",
					"nov", "dec", "sun", "mon", "tue", "wed", "thu", "fri", "sat"};
	int value[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4, 5, 6};
	for (int i = 0; i < 19; i++) {
		num[key[i]] = value[i];
	}
}

int get(string str) {
	if (str[0] >= '0' && str[0] <= '9') {
		return stoi(str);
	}
	string s;
	for (auto c : str) {
		s += tolower(c);
	}
	return num[s];
}

void work(string str, bool st[], int len) {
	if (str == "*") {
		for (int i = 0; i < len; i++) {
			st[i] = true;
		}
	} else {
		for (int i = 0; i < (int)str.size(); i++) {
			int j = i + 1;
			while (j < (int)str.size() && str[j] != ',') {
				++j;
			}
			string s = str.substr(i, j - i);
			i = j;
			int k = s.find('-');
			if (k != -1) {
				int l = get(s.substr(0, k)), r = get(s.substr(k + 1));
				for (int u = l; u <= r; u++) {
					st[u] = true;
				}
			} else {
				st[get(s)] = true;
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	int n;
	string sta, end;
	cin >> n >> sta >> end;
	init();
	task.resize(n);
	for (int i = 0; i < n; i++) {
		string mm, hh, d, m, w, cmd;
		cin >> mm >> hh >> d >> m >> w >> cmd;
		work(mm, task[i].mm, 60);
		work(hh, task[i].hh, 24);
		work(d, task[i].d, 32);
		work(m, task[i].m, 13);
		work(w, task[i].w, 7);
		task[i].cmd = cmd;
	}
	Timer t("197001010000"), S(sta), E(end);
	t.w = 4;
	while (t < E) {
		if (!(t < S)) {
			for (int i = 0; i < n; i++) {
				if (task[i].check(t)) {
					cout << t.to_string() << " " << task[i].cmd << endl;
				}
			}
		}
		t.next();
	}

	return 0;
}