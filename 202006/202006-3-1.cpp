/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-25 10:01:43
 * 	modified: 	2024-07-31 20:45:26
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 20 * 1024 * 1024 + 10;

char str[maxn];
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
        return 0; // blank line
    } else if (s.size() >= 2 && s[0] == '*' && s[1] == ' ') {
        return 1; // item list
    } else if (s.size() >= 2 && s[0] == ' ' && s[1] == ' ') {
        return 2; // item in item list
    } else {
        return 3; // other
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

int wcl(string &s, int w) { // wc -l: word count -line
    int res = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == ' ') { // skip space in new line
            continue;
        }
        size_t j = i + 1;
        while (j < s.size() && j - i + 1 <= w) { // one line
            ++j;
        }
        ++res;
        i = j - 1;
    }
    return max(res, 1); // at least one line
}

int main(int argc, char const *argv[]) {

    int w;
    cin >> w;
    getchar();
    while (fgets(str, maxn, stdin)) {
        strs.emplace_back(str);
        if (strs.back().back() == '\n') {
            strs.back().pop_back();
        }
    }
    int r = -1, last = 0;
    // 0: paragraph, 1: item, 2: blank line
    for (size_t i = 0; i < strs.size();) {
        int t = judge(strs[i]);
        if (t == 0) { // blank line
            ++i, last = 2;
        } else if (t == 1) { // item list
            if (last != 1) { // new item list
                ++r;
            }
            last = 1;
            string line = trim(strs[i].substr(2));
            ++i;
            while (i < strs.size()) {
                if (judge(strs[i]) == 2) { // t = 2 after t = 1
                    // all item in the item list
                    line += ' ' + trim(strs[i].substr(2));
                    ++i;
                } else {
                    break;
                }
            }
            r += wcl(line, w - 3);
        } else { // paragraph: other, not include item in item list
            ++r;
            last = 0;
            string line = trim(strs[i]);
            ++i;
            while (i < strs.size()) {
                int t = judge(strs[i]);
                if (t == 2 || t == 3) { // t = 2 not after t = 1
                    line += ' ' + trim(strs[i]);
                    ++i;
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