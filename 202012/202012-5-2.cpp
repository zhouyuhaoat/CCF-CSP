// https://www.acwing.com/solution/content/40431
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 4e4 + 5, mod = 1e9 + 7;

struct query {
    ll op, l, r, x[3];
} a[maxn];

struct BIT {
    struct node {
        int l, r, c;
        ll val[3], tag[5];
    } tr[maxn * 40];
    void push_up(int rt) {
        for (int i = 0; i <= 2; i++) {
            tr[rt].val[i] = (tr[rt << 1].val[i] + tr[rt << 1 | 1].val[i]) % mod;
        }
    }
    void push_down(int rt) {
        if (tr[rt].tag[4] == 1) {
            swap(tr[rt << 1].val[0], tr[rt << 1].val[1]), swap(tr[rt << 1].val[1], tr[rt << 1].val[2]),
                swap(tr[rt << 1].tag[0], tr[rt << 1].tag[1]), swap(tr[rt << 1].tag[1], tr[rt << 1].tag[2]),
                swap(tr[rt << 1 | 1].val[0], tr[rt << 1 | 1].val[1]),
                swap(tr[rt << 1 | 1].val[1], tr[rt << 1 | 1].val[2]),
                swap(tr[rt << 1 | 1].tag[0], tr[rt << 1 | 1].tag[1]),
                swap(tr[rt << 1 | 1].tag[1], tr[rt << 1 | 1].tag[2]);
        }
        if (tr[rt].tag[4] == 2) {
            swap(tr[rt << 1].val[0], tr[rt << 1].val[2]), swap(tr[rt << 1].val[1], tr[rt << 1].val[2]),
                swap(tr[rt << 1].tag[0], tr[rt << 1].tag[2]), swap(tr[rt << 1].tag[1], tr[rt << 1].tag[2]),
                swap(tr[rt << 1 | 1].val[0], tr[rt << 1 | 1].val[2]),
                swap(tr[rt << 1 | 1].val[1], tr[rt << 1 | 1].val[2]),
                swap(tr[rt << 1 | 1].tag[0], tr[rt << 1 | 1].tag[2]),
                swap(tr[rt << 1 | 1].tag[1], tr[rt << 1 | 1].tag[2]);
        }
        if (tr[rt].tag[3] ^ 1) {
            for (int i = 0; i <= 2; i++) {
                tr[rt << 1].val[i] = tr[rt << 1].val[i] * tr[rt].tag[3] % mod,
                         tr[rt << 1].tag[i] = tr[rt << 1].tag[i] * tr[rt].tag[3] % mod,
                         tr[rt << 1 | 1].val[i] = tr[rt << 1 | 1].val[i] * tr[rt].tag[3] % mod,
                         tr[rt << 1 | 1].tag[i] = tr[rt << 1 | 1].tag[i] * tr[rt].tag[3] % mod;
            }
        }
        for (int i = 0; i <= 2; i++) {
            if (tr[rt].tag[i]) {
                tr[rt << 1].val[i] = (tr[rt << 1].val[i] + tr[rt].tag[i] * tr[rt << 1].c % mod) % mod,
                         tr[rt << 1].tag[i] = (tr[rt << 1].tag[i] + tr[rt].tag[i]) % mod,
                         tr[rt << 1 | 1].val[i] =
                             (tr[rt << 1 | 1].val[i] + tr[rt].tag[i] * tr[rt << 1 | 1].c % mod) % mod,
                         tr[rt << 1 | 1].tag[i] = (tr[rt << 1 | 1].tag[i] + tr[rt].tag[i]) % mod;
            }
        }
        tr[rt << 1].tag[3] = tr[rt << 1].tag[3] * tr[rt].tag[3] % mod;
        tr[rt << 1 | 1].tag[3] = tr[rt << 1 | 1].tag[3] * tr[rt].tag[3] % mod;
        tr[rt << 1].tag[4] = (tr[rt << 1].tag[4] + tr[rt].tag[4]) % 3;
        tr[rt << 1 | 1].tag[4] = (tr[rt << 1 | 1].tag[4] + tr[rt].tag[4]) % 3;
        memset(tr[rt].tag, 0, sizeof tr[rt].tag);
        tr[rt].tag[3] = 1;
    }
    void build(int rt, int l, int r, vector<int> &c) {
        tr[rt].l = l, tr[rt].r = r, tr[rt].c = c[r + 1] - c[l];
        memset(tr[rt].val, 0, sizeof tr[rt].val);
        memset(tr[rt].tag, 0, sizeof tr[rt].tag);
        tr[rt].tag[3] = 1;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid, c);
        build(rt << 1 | 1, mid + 1, r, c);
    }
    void change(int rt, query &q) {
        if (tr[rt].l >= q.l && tr[rt].r <= q.r) {
            if (q.op == 1) {
                for (int i = 0; i <= 2; i++) {
                    tr[rt].val[i] = (tr[rt].val[i] + q.x[i] * tr[rt].c % mod) % mod,
                    tr[rt].tag[i] = (tr[rt].tag[i] + q.x[i]) % mod;
                }
            } else if (q.op == 2) {
                for (int i = 0; i <= 2; i++) {
                    tr[rt].val[i] = tr[rt].val[i] * q.x[0] % mod, tr[rt].tag[i] = tr[rt].tag[i] * q.x[0] % mod;
                }
                tr[rt].tag[3] = tr[rt].tag[3] * q.x[0] % mod;
            } else {
                swap(tr[rt].val[0], tr[rt].val[1]), swap(tr[rt].val[1], tr[rt].val[2]);
                swap(tr[rt].tag[0], tr[rt].tag[1]), swap(tr[rt].tag[1], tr[rt].tag[2]);
                tr[rt].tag[4] = (tr[rt].tag[4] + 1) % 3;
            }
            return;
        }
        push_down(rt);
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        if (mid >= q.l) {
            change(rt << 1, q);
        }
        if (mid < q.r) {
            change(rt << 1 | 1, q);
        }
        push_up(rt);
    }
    query ask(int rt, int l, int r) {
        query ans, res;
        if (tr[rt].l >= l && tr[rt].r <= r) {
            return memcpy(ans.x, tr[rt].val, sizeof ans.x), ans;
        }
        push_down(rt);
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        if (mid >= l) {
            ans = ask(rt << 1, l, r);
        } else {
            memset(ans.x, 0, sizeof ans.x);
        }
        if (mid < r) {
            res = ask(rt << 1 | 1, l, r);
            for (int i = 0; i <= 2; i++) {
                ans.x[i] = (ans.x[i] + res.x[i]) % mod;
            }
        }
        return ans;
    }
} bit;

int n, m, _, k, cas;
vector<int> c;

int main(int argc, char const *argv[]) {

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i].op >> a[i].l >> a[i].r;
        c.emplace_back(a[i].l);
        c.emplace_back(a[i].r + 1);
        if (a[i].op == 1) {
            cin >> a[i].x[0] >> a[i].x[1] >> a[i].x[2];
        } else if (a[i].op == 2) {
            cin >> a[i].x[0];
        }
    }
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    bit.build(1, 0, c.size() - 1, c);
    for (int i = 1; i <= m; i++) {
        a[i].l = lower_bound(c.begin(), c.end(), a[i].l) - c.begin();
        a[i].r = upper_bound(c.begin(), c.end(), a[i].r) - c.begin() - 1;
        if (a[i].op ^ 4) {
            bit.change(1, a[i]);
        } else {
            a[i] = bit.ask(1, a[i].l, a[i].r);
            ll ans = 0;
            for (int j = 0; j <= 2; j++) {
                ans = (ans + a[i].x[j] * a[i].x[j]) % mod;
            }
            cout << ans << '\n';
        }
    }

    return 0;
}