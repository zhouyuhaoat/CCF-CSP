/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-01 10:42:11
 * 	modified: 	2024-08-01 11:06:32
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
/*
Aho-Corasick Automaton
Dynamic Programming
https://www.acwing.com/activity/content/code/content/984952
*/
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 55, maxm = 1010, mod = 998244353;

struct node {
    int row, next;
} g[26][maxn];

int tr[maxn][26], cnt[maxn], idx, ne[maxn];
int f[maxm][maxn][maxn];
vector<string> str;

void insert(string s) {
    int p = 0;
    for (char c : s) {
        int u = c - 'a';
        if (tr[p][u] == 0) {
            tr[p][u] = ++idx;
        }
        p = tr[p][u];
    }
    ++cnt[p];
}

void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (tr[0][i] != 0) {
            q.emplace(tr[0][i]);
        }
    }
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            int p = tr[t][i];
            if (p == 0) {
                tr[t][i] = tr[ne[t]][i];
            } else {
                ne[p] = tr[ne[t]][i];
                cnt[p] += cnt[ne[p]];
                q.emplace(p);
            }
        }
    }
}

int main(int argc, char const *argv[]) {

    int n, m;
    cin >> n >> m;
    string s;
    for (int i = 0; i < 26; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> s;
            g[s[0] - 'a'][j] = {i, stoi(s.substr(1))};
        }
    }
    while (cin >> s) {
        insert(s);
        str.emplace_back(s);
    }
    build();
    f[0][0][1] = 1;
    for (int i = 0; i <= m; i++) {
        int sum = 0;
        for (int j = 0; j <= idx; j++) {
            for (int k = 1; k <= n; k++) {
                if (f[i][j][k] == 0) {
                    continue;
                }
                sum = (sum + f[i][j][k]) % mod;
                for (string s : str) {
                    if (i + s.size() > m) {
                        continue;
                    }
                    bool flag = true;
                    int x = j, y = k;
                    for (char c : s) {
                        int u = c - 'a';
                        node t = g[u][y];
                        x = tr[x][t.row];
                        if (cnt[x] != 0) {
                            flag = false;
                            break;
                        }
                        y = t.next;
                    }
                    if (flag) {
                        int &v = f[i + s.size()][x][y];
                        v = (v + f[i][j][k]) % mod;
                    }
                }
            }
        }
        if (i != 0) {
            cout << sum << "\n";
        }
    }

    return 0;
}