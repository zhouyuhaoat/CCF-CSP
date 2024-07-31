/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-25 22:12:04
 * 	modified: 	2024-07-30 22:28:31
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 14, mod = 998244353;

int id[100], u[maxn] = {1, 2, 4, 6, 16, 26, 41, 42, 44, 46, 61, 62, 64, 66};
vector<int> v[maxn] = {{2}, {4}, {1, 6, 16}, {6, 4, 64}, {26}, {46}, {62}, {64}, {61}, {66}, {42}, {44}, {41}, {46}};
int trans[maxn][maxn]; // transition matrix: edge (u, v) in graph

/*
1 -> 2 -> 4 -> 1, 6, 16 -> 26(4) -> 46(4) -> (1)66(4) -> (6)46(4)
6 -> 6, 4, 64 -> (6)41(6) -> (1)62 -> (6)44 -> (1)61(6) -> (6)42 -> (1)64
11, 12, 14, 21, 22, 24: impossible

1-bit -> 1-bit: 1 -> 2; 2 -> 4; 4 -> 1, 6; 6 -> 6, 4
1-bit -> 2-bit: 4 -> 16; 6 -> 64
2-bit -> 2-bit: 16 -> 26 -> 46 -> 66 -> 46; 64 -> 41 -> 62 -> 44 -> 61 -> 42 -> 64
some 2-bit only transitioned from 1-bit: 4 -> 16; 6 -> 64

n.S: n = second; S = string
0.1: 1
1.2: 1 -> 2
2.4: 2 -> 4
3.16: 4 -> 1, 6, 16
4.264: 1 -> 2; 6 -> 6, 4, 64; 16 -> 26
5.46416: 2 -> 4, 6 -> 6, 4, 64; 4 -> 1, 6, 16; 64 -> 41; 26 -> 46
*/

void mul(int c[][maxn], int a[][maxn], int b[][maxn]) {
    static int t[maxn][maxn];
    memset(t, 0, sizeof(t));
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            for (int k = 0; k < maxn; k++) {
                t[i][j] = (t[i][j] + (long long)a[i][k] * b[k][j]) % mod;
            }
        }
    }
    memcpy(c, t, sizeof(t));
}

int exp(int k, int id) {
    if (id == -1) {
        return 0;
    }
    int res[maxn][maxn] = {}, b[maxn][maxn];
    memcpy(b, trans, sizeof(b));
    res[0][0] = 1; // initial state: 0.1
    while (k != 0) {
        if (k & 1) {
            mul(res, res, b);
        }
        mul(b, b, b);
        k >>= 1;
    }
    return res[0][id]; // count the number of string's id
}

string get(string s) { // scan second by second: trace back
    string res;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '2') {
            res += '1'; // 1 -> 2
        } else if (s[i] == '4') {
            res += '2'; // 2 -> 4
            // 6 -> (6)4: skip when scan the prefix 6
        } else if (s[i] == '1') {
            if (i + 1 == s.size() || s[i + 1] == '6') {
                res += '4', ++i; // 4 -> 1(6): skip the suffix 6
            } else {
                return ""; // empty string: mis-match
            }
        } else {
            if (i + 1 == s.size() || s[i + 1] == '4') {
                res += '6', ++i; // 6 -> 6(4): skip the suffix 4
            } else {
                return "";
            }
        }
        // 1 or 6 is the last char of string: add suffix 6 or 4 since 16 or 64
    }
    return res;
}

int dfs(int k, string &s) {
    if (s.size() <= 2) { // |S| = 1 or 2
        return exp(k, id[stoi(s)]);
    }
    int res = 0;
    // 6 or 4 is the first char of string: add prefix 1 or 6 since 16 or 64
    // 3 prefix: only one is needed, others return empty string or return 0 after recursion
    for (string c : {"", "1", "6"}) {
        string t = get(c + s);
        if (t.size() > 0) {
            res = (res + dfs(k - 1, t)) % mod; // |S| > 2
        }
    }
    return res;
}

int main(int argc, char const *argv[]) {

    int n;
    string s;
    cin >> n >> s;
    memset(id, -1, sizeof(id));
    for (int i = 0; i < maxn; i++) {
        id[u[i]] = i; // vertex -> id
    }
    for (int i = 0; i < maxn; i++) {
        for (int x : v[i]) {
            ++trans[i][id[x]]; // id -> id
        }
    }
    cout << dfs(n, s) << "\n";

    return 0;
}