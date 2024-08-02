// https://www.acwing.com/solution/content/66676
#include <iostream>

using namespace std;

const int maxn = 105, maxk = 15, inf = 2147483647;

int n, m, k;
bool mp[maxn][maxk];

int head[maxn], trump;
struct edge {
    int to, next, val;
    edge(int u = 0, int v = 0, int w = 0) : to(v), next(head[u]), val(w) {};
} e[maxn << 1];
void addedge(int u, int v, int w) {
    e[++trump] = edge(u, v, w);
    head[u] = trump;
    e[++trump] = edge(v, u, w);
    head[v] = trump;
}

int f[maxk][maxn];
int dp[maxn], len[maxn], sze[maxn];
void calc(int u, int fa) {
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) {
            continue;
        }
        calc(v, u);
        sze[u] += sze[v];
        if (sze[v] == 0) {
            continue;
        }
        dp[u] += dp[v] + 2 * e[i].val;
        len[u] = max(len[u], len[v] + e[i].val);
    }
}

int bel[maxn], ans = inf;
int s[maxk][maxk], cnt[maxk], res[maxk];

void solve() {
    for (int i = 1; i <= k; ++i) {
        s[bel[i]][++cnt[bel[i]]] = i;
    }
    for (int i = 1; i <= m; ++i) {
        res[i] = inf;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int tmp = 0;
            for (int l = 1; l <= cnt[j]; ++l) {
                tmp = max(tmp, f[s[j][l]][i]);
            }
            res[j] = min(res[j], tmp);
        }
    }
    int tmp = 0;
    for (int i = 1; i <= m; ++i) {
        tmp = max(tmp, res[i]), cnt[i] = 0;
    }
    ans = min(ans, tmp);
}

void dfs(int dep, int cnt) {
    if (dep > k) {
        if (cnt == m) {
            solve();
        }
        return;
    }
    for (int i = 1; i <= cnt + 1; ++i) {
        bel[dep] = i;
        dfs(dep + 1, max(cnt, i));
    }
}

int main(int argc, char const *argv[]) {

    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            cin >> mp[i][j];
        }
    }
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        addedge(u, v, w);
    }
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int l = 1; l <= n; ++l) {
                dp[l] = len[l] = 0;
                sze[l] = mp[l][i];
            }
            calc(j, 0);
            f[i][j] = dp[j] - len[j];
        }
    }
    dfs(1, 0);
    cout << ans << "\n";

    return 0;
}