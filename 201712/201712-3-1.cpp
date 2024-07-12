/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-20 21:06:58
 * 	modified: 	2024-07-12 21:32:26
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct stamp {
	string time;
	int y, m, d, hh, mm;
} st, en;

struct crontab {
	vector<pair<int, int>> time[5]; // pair: range
	string cmd;
};

struct task {
	long long time;
	string cmd;
	int id;
	task(long long time, string cmd, int id) : time(time), cmd(cmd), id(id) {
	}
	bool operator<(const task &a) const {
		return time == a.time ? (id < a.id) : (time < a.time);
	}
};

vector<crontab> cron;
vector<task> ans;

int md[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
				 {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

map<string, int> mw = {{"jan", 1}, {"feb", 2}, {"mar", 3},	{"apr", 4},	 {"may", 5},  {"jun", 6}, {"jul", 7},
					   {"aug", 8}, {"sep", 9}, {"oct", 10}, {"nov", 11}, {"dec", 12}, {"sun", 0}, {"mon", 1},
					   {"tue", 2}, {"wed", 3}, {"thu", 4},	{"fri", 5},	 {"sat", 6}};

int isleap(int y) {
	return (!(y % 400) || (!(y % 4) && (y % 100)));
}

int zeller(int y, int m, int d) { // Zeller's Congruence
	if (m < 3) {
		m += 12;
		--y;
	}
	int c = y / 100, yofc = y % 100;
	int h = (d + ((13 * (m + 1)) / 5) + yofc + (yofc / 4) + (c / 4) - (2 * c)) % 7;
	return (h + 6) % 7; // begin with: saturday -> sunday
}

int getv(string s) {
	if (isdigit(s[0])) {
		return stoi(s);
	} else {
		return mw[s];
	}
}

stamp trans(string s) {
	return {s,
			stoi(s.substr(0, 4)),
			stoi(s.substr(4, 2)),
			stoi(s.substr(6, 2)),
			stoi(s.substr(8, 2)),
			stoi(s.substr(10, 2))};
}

void read(crontab &input) {
	for (int i = 0; i < 5; i++) {
		string s;
		cin >> s;
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		stringstream ss;
		ss << s;
		vector<string> w;
		while (getline(ss, s, ',')) {
			w.emplace_back(s);
		}
		if (w[0] == "*") {
			input.time[i].emplace_back(-1, -1);
			continue;
		}
		for (int j = 0; j < (int)w.size(); j++) {
			size_t p = w[j].find('-');
			int v1 = -1, v2 = -1;
			if (p == string::npos) {
				v1 = getv(w[j]), v2 = getv(w[j]);
			} else {
				v1 = getv(w[j].substr(0, p)), v2 = getv(w[j].substr(p + 1));
			}
			input.time[i].emplace_back(v1, v2);
		}
	}
	cin >> input.cmd;
}

bool islaw(int t, vector<pair<int, int>> r) {
	if (r[0].first == -1) { // *: -1 -> -1
		return true;
	}
	for (int i = 0; i < (int)r.size(); i++) {
		if (t >= r[i].first && t <= r[i].second) {
			return true;
		}
	}
	return false;
}

bool isend(int y, int m, int d, int hh, int mm) {
	if (y > en.y) {
		return true;
	}
	if (y < en.y) {
		return false;
	}
	if (m > en.m) {
		return true;
	}
	if (m < en.m) {
		return false;
	}
	if (d > en.d) {
		return true;
	}
	if (d < en.d) {
		return false;
	}
	if (hh > en.hh) {
		return true;
	}
	if (hh < en.hh) {
		return false;
	}
	if (mm > en.mm) {
		return true;
	}
	if (mm < en.mm) {
		return false;
	}
	return true; // all equal
}

void judge(crontab &input, int id) {
	int y = st.y, m = st.m, d = st.d, hh = st.hh, mm = st.mm;
	for (; y <= en.y; y++, m = 1) {
		for (; m <= 12; m++, d = 1) {
			if (islaw(m, input.time[3])) {
				int dd = md[isleap(y)][m];
				for (; d <= dd; d++, hh = 0) {
					if (islaw(d, input.time[2]) && islaw(zeller(y, m, d), input.time[4])) {
						for (; hh < 24; hh++, mm = 0) {
							if (islaw(hh, input.time[1])) {
								for (; mm < 60; mm++) {
									if (isend(y, m, d, hh, mm)) {
										goto end;
										break;
									}
									if (islaw(mm, input.time[0])) {
										long long time = (long long)y * 1e8 + m * 1e6 + d * 1e4 + hh * 1e2 + mm;
										ans.emplace_back(time, input.cmd, id);
									}
								}
							}
						}
					}
				}
			}
		}
	}
end:;
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	cron.resize(n);
	cin >> st.time >> en.time;
	st = trans(st.time), en = trans(en.time);
	for (int i = 0; i < n; i++) {
		read(cron[i]);
		judge(cron[i], i);
	}
	sort(ans.begin(), ans.end());
	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i].time << " " << ans[i].cmd << "\n";
	}

	return 0;
}