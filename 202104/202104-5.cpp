// https://www.acwing.com/activity/content/code/content/1156103
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 510;
const ll inf = 0x3f3f3f3f3f3f3f3fll;

struct node {
    int cid, sum, pid;
};

vector<node> ps[maxn];
vector<pii> line[maxn];
ll dist[maxn], ans[maxn];
int len[maxn], pid[maxn];
bool vis[maxn];

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

void dijkstra(int m) {
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 0; i < m; i++) {
        int d = 0;
        for (int j = 0; j < line[i].size(); j++) {
            if (line[i][j].first == 1) {
                dist[i] = d;
                pid[i] = j;
                break;
            }
            d += line[i][j].second;
        }
    }
    for (int i = 0; i < m; i++) {
        int t = -1;
        for (int j = 0; j < m; j++) {
            if (!vis[j] && (t == -1 || dist[j] < dist[t])) {
                t = j;
            }
        }
        vis[t] = true;
        vector<pii> &l = line[t];
        ll d = dist[t];
        for (int j = pid[t], k = 0; k < l.size(); j = (j + 1) % l.size(), k++) {
            for (auto &c : ps[l[j].first]) {
                if (vis[c.cid]) {
                    continue;
                }
                ll a = d, b = len[t];
                ll x = c.sum, y = len[c.cid];
                ll X, Y;
                ll D = exgcd(b, y, X, Y);
                if ((x - a) % D != 0) {
                    continue;
                }
                X = (x - a) / D * X;
                y /= D;
                X = (X % y + y) % y;
                if (dist[c.cid] > a + b * X) {
                    dist[c.cid] = a + b * X;
                    pid[c.cid] = c.pid;
                }
            }
            d += l[j].second;
        }
    }
}

int main(int argc, char const *argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int cnt, sum = 0;
        cin >> cnt;
        for (int j = 0; j < cnt; j++) {
            int ver, t;
            cin >> ver >> t;
            ps[ver].emplace_back(node{i, sum, j});
            line[i].emplace_back(ver, t);
            sum += t;
        }
        len[i] = sum;
    }
    dijkstra(m);
    memset(ans, 0x3f, sizeof(ans));
    for (int i = 0; i < m; i++) {
        if (dist[i] == inf) {
            continue;
        }
        ll d = dist[i];
        for (int j = pid[i], k = 0; k < line[i].size(); j = (j + 1) % line[i].size(), k++) {
            int ver = line[i][j].first;
            ans[ver] = min(ans[ver], d);
            d += line[i][j].second;
        }
    }
    for (int i = 2; i <= n; i++) {
        ans[i] == inf ? cout << "inf\n" : cout << ans[i] << "\n";
    }

    return 0;
}