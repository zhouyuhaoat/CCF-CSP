// https://www.acwing.com/activity/content/code/content/979737
#include <cstring>
#include <iostream>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 110, maxm = 10, maxs = 1 << maxm;

int n, m, k;
int need[maxn][maxm];
int h[maxn], e[maxn * 2], w[maxn * 2], ne[maxn * 2], idx;
int d[maxn][maxm];
int f[maxs], state[maxn];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

pii dfs(int u, int fa, int v) {
    pii res(0, -1);
    if (need[u][v]) {
        res.y = 0;
    }
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) {
            continue;
        }
        pii t = dfs(j, u, v);
        if (t.y != -1) {
            res.x += t.x + w[i] * 2;
            res.y = max(res.y, t.y + w[i]);
        }
    }
    return res;
}

bool check(int mid) {
    memset(state, 0, sizeof(state));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            if (d[i][j] <= mid) {
                state[i] |= 1 << j;
            }
        }
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 0; i < 1 << k; i++) {
        for (int j = 1; j <= n; j++) {
            f[i | state[j]] = min(f[i | state[j]], f[i] + 1);
        }
    }
    return f[(1 << k) - 1] <= m;
}

int main(int argc, char const *argv[]) {

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> need[i][j];
        }
    }
    memset(h, -1, sizeof(h));
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            pii t = dfs(i, -1, j);
            if (t.y != -1) {
                d[i][j] = t.x - t.y;
            }
        }
    }
    int l = 0, r = 2e8;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << r << "\n";

    return 0;
}