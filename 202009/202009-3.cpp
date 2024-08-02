/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-01 11:34:30
 * 	modified: 	2024-08-02 10:49:30
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// https://www.acwing.com/activity/content/code/content/935832
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 3010, maxm = maxn * 5;

int w[maxn], f[maxn];
int h[maxn], e[maxm], ne[maxm], idx;
int d[maxn];
vector<int> in[maxm], out[maxm], topo;

int get(string func) {
    string funcs[] = {"AND", "OR", "NOT", "XOR", "NAND", "NOR"};
    for (int i = 0; i < 6; i++) {
        if (funcs[i] == func) {
            return i;
        }
    }
    return -1;
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    ++d[b];
}

bool toposort(int m, int n) {
    topo.clear(); // @importrant: array -> vector
    queue<int> q;
    for (int i = 1; i <= m + n; i++) {
        if (d[i] == 0) {
            q.emplace(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.emplace_back(u);
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (--d[v] == 0) {
                q.emplace(v);
            }
        }
    }
    return topo.size() == m + n;
}

int main(int argc, char const *argv[]) {

    int Q;
    cin >> Q;
    while (Q--) {
        int m, n;
        cin >> m >> n;
        memset(h, -1, sizeof(h)), idx = 0;
        memset(d, 0, sizeof(d));
        for (int i = 1; i <= n; i++) {
            string func;
            int k;
            cin >> func >> k;
            f[m + i] = get(func);
            while (k--) {
                string l;
                cin >> l;
                int t = stoi(l.substr(1));
                if (l[0] == 'I') {
                    add(t, m + i);
                } else {
                    add(m + t, m + i);
                }
            }
        }
        int S;
        cin >> S;
        for (int i = 0; i < S; i++) {
            in[i].clear();
            for (int j = 0; j < m; j++) {
                int x;
                cin >> x;
                in[i].emplace_back(x);
            }
        }
        for (int i = 0; i < S; i++) {
            out[i].clear();
            int s;
            cin >> s;
            while (s--) {
                int x;
                cin >> x;
                out[i].emplace_back(x);
            }
        }
        if (!toposort(m, n)) {
            cout << "LOOP\n";
        } else {
            for (int i = 0; i < S; i++) {
                for (int j = 0; j < m; j++) {
                    w[j + 1] = in[i][j];
                }
                for (int j = m + 1; j <= m + n; j++) {
                    if (f[j] == 0 || f[j] == 5) {
                        w[j] = 1;
                    } else {
                        w[j] = 0;
                    }
                }
                for (int j = 0; j < m + n; j++) {
                    int t = topo[j], v = w[t];
                    for (int k = h[t]; ~k; k = ne[k]) {
                        int u = e[k];
                        switch (f[u]) {
                            case 0:
                                w[u] &= v;
                                break;
                            case 1:
                                w[u] |= v;
                                break;
                            case 2:
                                w[u] = !v;
                                break;
                            case 3:
                                w[u] ^= v;
                                break;
                            case 4:
                                w[u] |= !v;
                                break;
                            default:
                                w[u] &= !v;
                        }
                    }
                }
                for (int j = 0; j < out[i].size(); j++) {
                    cout << w[m + out[i][j]];
                    j < out[i].size() - 1 ? cout << " " : cout << "\n";
                }
            }
        }
    }

    return 0;
}