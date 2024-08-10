// https://www.acwing.com/activity/content/code/content/2120840
#include <iostream>
#include <vector>

#define x first
#define y second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 300010;

int p;

struct node {
    int s[2], p, v;
    int rev;
    int sum, mul;
} tr[maxn];

int stk[maxn], idx;
int fa[maxn], dep[maxn];
int A;
vector<pii> level[maxn];

void pushrev(int x) {
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x) {
    tr[x].sum = tr[x].v;
    int l = tr[x].s[0], r = tr[x].s[1];
    if (l != 0) {
        tr[x].sum = (tr[x].sum + tr[l].sum) % p;
    }
    if (r != 0) {
        tr[x].sum += tr[r].sum;
    }
    tr[x].sum %= p;
}

void pushdown(int x) {
    if (tr[x].rev) {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
    auto &root = tr[x], &left = tr[tr[x].s[0]], &right = tr[tr[x].s[1]];
    if (root.mul != 1) {
        ll mul = root.mul;
        left.v = left.v * mul % p;
        left.sum = left.sum * mul % p;
        left.mul = left.mul * mul % p;
        right.v = right.v * mul % p;
        right.sum = right.sum * mul % p;
        right.mul = right.mul * mul % p;
        root.mul = 1;
    }
}

bool isroot(int x) {
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y))
        tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x) {
    int top = 0, r = x;
    stk[++top] = r;
    while (!isroot(r)) {
        stk[++top] = r = tr[r].p;
    }
    while (top) {
        pushdown(stk[top--]);
    }
    while (!isroot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y)) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) {
                rotate(x);
            } else {
                rotate(y);
            }
        }
        rotate(x);
    }
}

void access(int x) {
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p) {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x) {
    access(x);
    pushrev(x);
}

int findroot(int x) {
    access(x);
    while (tr[x].s[0] != 0) {
        pushdown(x), x = tr[x].s[0];
    }
    splay(x);
    return x;
}

void split(int x, int y) {
    makeroot(x);
    access(y);
}

void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
        tr[x].p = y;
    }
}

int find(int x, int y) {
    int l = 0, r = level[x].size() - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (level[x][mid].x <= y) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return level[x][r].y;
}

int main(int argc, char const *argv[]) {

    int n, T;
    cin >> n >> p >> T;
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            x ^= A;
            if (x > 0) {
                ++idx;
                tr[idx].sum = tr[idx].v = x;
                tr[idx].mul = 1;
                if (cur != 0) {
                    link(cur, idx);
                }
                fa[idx] = cur, dep[idx] = dep[cur] + 1;
                cur = idx;
                level[dep[cur]].push_back({i, cur});
            } else {
                cur = fa[cur];
            }
        } else if (op == 2) {
            int s, l, r, y;
            cin >> s >> l >> r >> y;
            y ^= A;
            l = find(l, s), r = find(r, s);
            split(l, r);
            tr[r].v = tr[r].v * (ll)y % p;
            tr[r].sum = tr[r].sum * (ll)y % p;
            tr[r].mul = tr[r].mul * (ll)y % p;
        } else {
            int s, l, r;
            cin >> s >> l >> r;
            l = find(l, s), r = find(r, s);
            split(l, r);
            cout << tr[r].sum << "\n";
            if (T != 0) {
                A = tr[r].sum;
            }
        }
    }

    return 0;
}