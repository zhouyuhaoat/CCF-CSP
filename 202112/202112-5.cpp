// https://www.silllage.com/ccf-csp-24-e
// Time Limit Exceeded in AcWing 4284
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#pragma GCC optimize(3)

using namespace std;

const int maxn = 5e5 + 10, inf = 1e9 + 10;

vector<int> g[maxn];
int S, Mx, K1, K2, n, root;
int sm[maxn], mxson[maxn], vis[maxn];
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)

inline int rd() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + (ch ^ 48), ch = getchar();
    }
    return x * f;
}

void getrt(int u, int fa) {
    sm[u] = 1;
    mxson[u] = 0;
    for (int v : g[u]) {
        if (!vis[v] && v != fa) {
            getrt(v, u);
            sm[u] += sm[v];
            mxson[u] = max(mxson[u], sm[v]);
        }
    }
    mxson[u] = max(mxson[u], S - sm[u]);
    if (mxson[u] < Mx) {
        root = u;
        Mx = mxson[u];
    }
}

void get(int u, int fa, vector<int> &nodes, pair<int, int> *value, int mn, int mx) {
    nodes.emplace_back(u);
    value[u].first = mn;
    value[u].second = mx;
    for (int v : g[u]) {
        if (!vis[v] && v != fa) {
            get(v, u, nodes, value, min(mn, v), max(mx, v));
        }
    }
}

int rt[maxn], sz[maxn * 20], ch[maxn * 20][2], top = 0;
int newnode(int x) {
    sz[++top] = sz[x];
    ch[top][0] = ch[x][0];
    ch[top][1] = ch[x][1];
    return top;
}

void ins(int &rt, int l, int r, int val) {
    rt = newnode(rt);
    ++sz[rt];
    int t = rt;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (val <= mid) {
            ch[t][0] = newnode(ch[t][0]), t = ch[t][0], sz[t]++, r = mid;
        } else {
            ch[t][1] = newnode(ch[t][1]), t = ch[t][1], sz[t]++, l = mid + 1;
        }
    }
}

int get(int rt, int l, int r, int x) {
    int cnt = 0;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (x <= mid) {
            rt = ch[rt][0], r = mid;
        } else {
            cnt += sz[ch[rt][0]], rt = ch[rt][1], l = mid + 1;
        }
    }
    cnt += sz[rt];
    return cnt;
}

long long solve(int v, int mn, int mx) {
    vector<int> nodes;
    static int w[maxn];
    static pair<int, int> value[maxn];
    get(v, 0, nodes, value, min(mn, v), max(mx, v));
    for (int i = 0; i < nodes.size(); i++) {
        w[i] = nodes[i];
    }
    sort(w, w + nodes.size());
    long long cnt = 0;
    top = 0;
    rt[0] = 0;
    for (int i = 0; i < nodes.size(); i++) {
        auto p = value[w[i]];
        if (i != 0) {
            rt[i] = rt[i - 1];
        }
        if (w[i] - K1 <= p.first) {
            ins(rt[i], 1, n, p.second);
        }
        if (w[i] + K2 >= p.second) {
            int nv = p.first + K1;
            int l = -1, r = nodes.size() - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (w[mid] > nv) {
                    r = mid - 1;
                } else {
                    l = mid;
                }
            }
            int pos = min(l, i);
            if (pos >= 0) {
                cnt += get(rt[pos], 1, n, w[i] + K2);
            }
        }
    }
    return cnt;
}

long long ans = 0;
void Divide(int rt) {
    ans += solve(rt, inf, 0);
    vis[rt] = 1;
    for (int v : g[rt]) {
        if (!vis[v]) {
            ans -= solve(v, rt, rt);
            S = sm[v];
            root = 0;
            Mx = inf;
            getrt(v, 0);
            Divide(root);
        }
    }
}

int main(int argc, char const *argv[]) {

    n = rd(), K1 = rd(), K2 = rd();
    for (int i = 1; i < n; i++) {
        int u, v;
        u = rd(), v = rd();
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    Mx = inf;
    S = n;
    getrt(1, 0);
    Divide(root);
    cout << ans << endl;

    return 0;
}