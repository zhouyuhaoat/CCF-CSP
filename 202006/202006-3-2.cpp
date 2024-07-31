/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-31 19:28:17
 * 	modified: 	2024-07-31 21:04:39
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

vector<string> strs;

bool isblank(string &s) {
    for (char c : s) {
        if (c != ' ') {
            return false;
        }
    }
    return true;
}

int judge(string &s) {
    if (isblank(s)) {
        return 0;
    } else if (s.size() >= 2 && s[0] == '*' && s[1] == ' ') {
        return 1;
    } else if (s.size() >= 2 && s[0] == ' ' && s[1] == ' ') {
        return 2;
    } else {
        return 3;
    }
}

string trim(string s) {
    size_t i = 0, j = s.size() - 1;
    while (i <= j && s[i] == ' ') {
        ++i;
    }
    while (i <= j && s[j] == ' ') {
        --j;
    }
    return s.substr(i, j - i + 1);
}

int wcl(string &s, int w) {
    int cnt = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            continue;
        }
        // directly reach before next line
        size_t j = min(s.size() - 1, i + w - 1);
        ++cnt;
        i = j;
    }
    return max(cnt, 1);
}

int main(int argc, char const *argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int w;
    cin >> w;
    // getchar();
    string str;
    while (getline(cin, str)) {
        strs.emplace_back(str);
    }
    int r = -1, last = 0;
    for (size_t i = 0; i < strs.size();) {
        int t = judge(strs[i]);
        if (t == 0) {
            ++i, last = 2;
        } else if (t == 1) {
            if (last != 1) {
                ++r;
            }
            last = 1;
            string line = trim(strs[i++].substr(2));
            while (i < strs.size()) {
                if (judge(strs[i]) == 2) {
                    line += ' ' + trim(strs[i++].substr(2));
                } else {
                    break;
                }
            }
            r += wcl(line, w - 3);
        } else {
            ++r;
            last = 0;
            string line = trim(strs[i++]);
            while (i < strs.size()) {
                int t = judge(strs[i]);
                if (t == 2 || t == 3) {
                    line += ' ' + trim(strs[i++]);
                } else {
                    break;
                }
            }
            r += wcl(line, w);
        }
    }
    cout << r << "\n";

    return 0;
}