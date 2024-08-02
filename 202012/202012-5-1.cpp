// https://www.acwing.com/activity/content/code/content/987439
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 80010, mod = 1e9 + 7;

struct que {
    int t, l, r, k, a, b, c;
} q[maxn];

vector<int> xs;

struct node {
    int l, r, k;
    int a[3], b[3], s[3];
    int get_len() {
        return xs[r] - xs[l - 1];
    }
} tr[maxn * 4];

int get(int x) {
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}

void pushup(int u) {
    int *l = tr[u << 1].s, *r = tr[u << 1 | 1].s;
    for (int i = 0; i < 3; i++) {
        tr[u].s[i] = (l[i] + r[i]) % mod;
    }
}

void rotate(int a[]) {
    int t = a[0];
    a[0] = a[1], a[1] = a[2], a[2] = t;
}

void eval(int u, int k) {
    k %= 3;
    for (int i = 0; i < k; i++) {
        rotate(tr[u].a), rotate(tr[u].b), rotate(tr[u].s);
    }
    tr[u].k += k;
}

void eval(int u, int a[], int b[]) {
    for (int i = 0; i < 3; i++) {
        tr[u].s[i] = ((ll)tr[u].s[i] * a[i] + (ll)tr[u].get_len() * b[i]) % mod;
        int c = (ll)tr[u].a[i] * a[i] % mod;
        int d = ((ll)tr[u].b[i] * a[i] + b[i]) % mod;
        tr[u].a[i] = c, tr[u].b[i] = d;
    }
}

void pushdown(int u) {
    eval(u << 1, tr[u].k), eval(u << 1 | 1, tr[u].k);
    tr[u].k = 0;
    eval(u << 1, tr[u].a, tr[u].b), eval(u << 1 | 1, tr[u].a, tr[u].b);
    for (int i = 0; i < 3; i++) {
        tr[u].a[i] = 1, tr[u].b[i] = 0;
    }
}

void build(int u, int l, int r) {
    tr[u] = {l, r};
    for (int i = 0; i < 3; i++) {
        tr[i].a[i] = 1;
    }
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void update(int u, int l, int r, int k, int a[], int b[]) {
    if (tr[u].l >= l && tr[u].r <= r) {
        eval(u, k), eval(u, a, b);
    } else {
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (l <= mid) {
            update(u << 1, l, r, k, a, b);
        }
        if (r > mid) {
            update(u << 1 | 1, l, r, k, a, b);
        }
        pushup(u);
    }
}

vector<int> query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return {tr[u].s[0], tr[u].s[1], tr[u].s[2]};
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    vector<int> res(3);
    if (l <= mid) {
        res = query(u << 1, l, r);
    }
    if (r > mid) {
        vector<int> t = query(u << 1 | 1, l, r);
        for (int i = 0; i < 3; i++) {
            res[i] = (res[i] + t[i]) % mod;
        }
    }
    return res;
}

int main(int argc, char const *argv[]) {

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        q[i].k = 1;
        cin >> q[i].t >> q[i].l >> q[i].r;
        if (q[i].t == 1) {
            cin >> q[i].a >> q[i].b >> q[i].c;
        } else if (q[i].t == 2) {
            cin >> q[i].k;
        }
        xs.emplace_back(q[i].l - 1);
        xs.emplace_back(q[i].r);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    build(1, 0, xs.size() - 1);
    for (int i = 0; i < m; i++) {
        int t = q[i].t, l = get(q[i].l - 1) + 1, r = get(q[i].r);
        int a[] = {q[i].k, q[i].k, q[i].k}, b[] = {q[i].a, q[i].b, q[i].c};
        if (t == 1 || t == 2) {
            update(1, l, r, 0, a, b);
        } else if (t == 3) {
            update(1, l, r, 1, a, b);
        } else {
            vector<int> t = query(1, l, r);
            ll sum = 0;
            for (int j = 0; j < 3; j++) {
                sum += (ll)t[j] * t[j];
            }
            cout << sum % mod << "\n";
        }
    }

    return 0;
}