/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-26 16:34:41
 * 	modified: 	2024-07-31 09:50:25
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
/*
maximum weight closed subgraph
1. minimum cut
2. maximum flow
3. vertex splitting
- https://oi-wiki.org/graph/flow/min-cut/#问题模型-2
*/
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 2e4 + 10, maxm = (3e4 + 1e5) * 2 + 10, inf = 1e9;

int S, T;
int h[maxn], e[maxm], ne[maxm], idx;
long long c[maxm];
int d[maxn], cur[maxn];

void add(int a, int b, int w) {
    e[idx] = b, c[idx] = w, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, c[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() { // layer graph
    memset(d, -1, sizeof(d));
    queue<int> q;
    d[S] = 0, q.emplace(S), cur[S] = h[S];
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (d[v] == -1 && c[i] != 0) {
                d[v] = d[u] + 1;
                cur[v] = h[v];
                if (v == T) {
                    return true;
                }
                q.emplace(v);
            }
        }
    }
    return false;
}

long long dfs(int u, long long limit) { // blocking flow
    if (u == T) {
        return limit;
    }
    long long flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        cur[u] = i; // current arc optimization
        int v = e[i];
        if (d[v] == d[u] + 1 && c[i] != 0) {
            long long t = dfs(v, min(c[i], limit - flow));
            if (t == 0) {
                d[v] = -1;
                continue;
            }
            c[i] -= t, c[i ^ 1] += t;
            flow += t;
        }
    }
    return flow;
}

long long dinic() {
    long long flow = 0;
    while (bfs()) {
        long long delta;
        while ((delta = dfs(S, 1e18)) != 0) {
            flow += delta;
        }
    }
    return flow;
}

int calc(int x1, int x2, int a, int b, int c) {
    // calculate the maximum value of the quadratic or linear function
    int x[5] = {x1, x2};
    if (a != 0) {
        x[2] = -b / (a * 2);
        x[3] = x[2] - 1, x[4] = x[2] + 1;
    }
    int res = -inf;
    for (int v : x) {
        if (v >= x1 && v <= x2) {
            res = max(res, a * v * v + b * v + c);
        }
    }
    return res;
}

int main(int argc, char const *argv[]) {

    int n, m;
    cin >> n >> m;
    S = 0, T = n * 2 + 1;
    memset(h, -1, sizeof(h));
    long long tot = 0;
    for (int i = 1; i <= n; i++) {
        int l, r, a, b, c;
        cin >> l >> r >> a >> b >> c;
        // [0, 0]; [L, L]; (L, R); [R, R]
        int w1 = calc(l + 1, r - 1, a, b, c);
        int w2 = calc(l, r, a, b, c) - w1; // [L, R] - (L, R) = [L, L] + [R, R] = L, R
        w1 > 0 ? tot += w1, add(S, i, w1) : add(i, T, -w1);
        w2 > 0 ? tot += w2, add(S, n + i, w2) : add(n + i, T, -w2);
        add(n + i, i, inf); // L, R -> (L, R) => [L, R]
    }
    while (m--) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            add(y, x, inf); // (L, R): y -> x
        } else {
            add(n + y, x, inf); // L, R: y -> x
        }
    }
    cout << tot - dinic() << "\n";

    return 0;
}