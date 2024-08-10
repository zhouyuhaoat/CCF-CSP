// https://www.acwing.com/solution/content/219960
#include <algorithm>
#include <vector>

using namespace std;

int rd() {
    int k = 0, f = 1;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-') {
            f = -1;
        }
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        k = (k << 1) + (k << 3) + (s ^ '0');
        s = getchar();
    }
    return f > 0 ? k : -k;
}

void wr(int x) {
    if (x < 0) {
        putchar('-'), x = -x;
    }
    if (x > 9) {
        wr(x / 10);
    }
    putchar((x % 10) ^ '0');
}

struct dynamic_segment_tree {
    static const int INF = 1000000000;
    static const int NOT_ONLY = 1145141919;
    struct info_node {
        int id, pre_id, val;
        bool tag_id, tag_pre, tag_val;
    };
    struct node {
        int lc, rc;
        info_node info;
    };
    vector<node> tr;
    int rt;
    int interval_L, interval_R;

    dynamic_segment_tree(int L = 1, int R = INF) {
        interval_L = L, interval_R = R;
        tr.clear(), tr.resize(2), rt = 1;
    }

    void alloc_lchild(int u) {
        if (tr[u].lc == 0) {
            tr[u].lc = tr.size(), tr.push_back(node());
        }
    }

    void alloc_rchild(int u) {
        if (tr[u].rc == 0) {
            tr[u].rc = tr.size(), tr.push_back(node());
        }
    }

    void alloc_childs(int u) {
        alloc_lchild(u), alloc_rchild(u);
    }

    void pushup(int u) {
        int lc = tr[u].lc, rc = tr[u].rc;
        if (tr[lc].info.id == tr[rc].info.id && tr[lc].info.id != -1) {
            tr[u].info.id = tr[lc].info.id;
            if (tr[u].info.id == 0 && tr[lc].info.pre_id == tr[rc].info.pre_id) {
                tr[u].info.pre_id = tr[lc].info.pre_id;
            } else {
                tr[u].info.pre_id = -1;
            }
            if (tr[lc].info.val == tr[rc].info.val) {
                tr[u].info.val = tr[lc].info.val;
            } else {
                tr[u].info.val = NOT_ONLY;
            }
        } else {
            tr[u].info.id = -1;
        }
    }

    void pushdown(int u) {
        alloc_childs(u);
        int lc = tr[u].lc, rc = tr[u].rc;
        if (tr[u].info.tag_id) {
            tr[lc].info.tag_id = tr[rc].info.tag_id = 1;
            tr[lc].info.id = tr[rc].info.id = tr[u].info.id;
            tr[u].info.tag_id = 0;
        }
        if (tr[u].info.tag_pre) {
            tr[lc].info.tag_pre = tr[rc].info.tag_pre = 1;
            tr[lc].info.pre_id = tr[rc].info.pre_id = tr[u].info.pre_id;
            tr[u].info.tag_pre = 0;
        }
        if (tr[u].info.tag_val) {
            tr[lc].info.tag_val = tr[rc].info.tag_val = 1;
            tr[lc].info.val = tr[rc].info.val = tr[u].info.val;
            tr[u].info.tag_val = 0;
        }
    }

    int _search(int u, int L, int R, int l, int r, int id) {
        if (tr[u].info.id != -1) {
            return (tr[u].info.id == id || tr[u].info.id == 0) ? min(R, r) : -1;
        }
        pushdown(u);
        int M = (L + R) >> 1;
        if (l > M) {
            return _search(tr[u].rc, M + 1, R, l, r, id);
        }
        if (r <= M) {
            return _search(tr[u].lc, L, M, l, r, id);
        }
        int res = _search(tr[u].lc, L, M, l, r, id);
        if (res == M) {
            res = max(res, _search(tr[u].rc, M + 1, R, l, r, id));
        }
        return res;
    }

    int search(int l, int r, int id) {
        return _search(rt, interval_L, interval_R, l, r, id);
    }

    void _set(int u, int L, int R, int l, int r, int id, int val) {
        if (R < l || L > r) {
            return;
        }
        if (l <= L && R <= r) {
            tr[u].info.id = id, tr[u].info.val = val;
            tr[u].info.tag_id = tr[u].info.tag_val = 1;
            return;
        }
        pushdown(u);
        int M = (L + R) >> 1;
        _set(tr[u].lc, L, M, l, r, id, val);
        _set(tr[u].rc, M + 1, R, l, r, id, val);
        pushup(u);
    }

    void set(int l, int r, int id, int val) {
        _set(rt, interval_L, interval_R, l, r, id, val);
    }

    int set_real(int l, int r, int id, int val) {
        int real_r = search(l, r, id);
        if (real_r != -1) {
            set(l, real_r, id, val);
        }
        return real_r;
    }

    int find_id(int u, int L, int R, int l, int r, int id, bool cur_or_pre) {
        if (l <= L && R <= r) {
            if (cur_or_pre) {
                return tr[u].info.id;
            } else {
                return tr[u].info.id == 0 ? tr[u].info.pre_id : -1;
            }
        }
        pushdown(u);
        int M = (L + R) >> 1;
        if (l > M) {
            return find_id(tr[u].rc, M + 1, R, l, r, id, cur_or_pre);
        }
        if (r <= M) {
            return find_id(tr[u].lc, L, M, l, r, id, cur_or_pre);
        }
        int l_res = find_id(tr[u].lc, L, M, l, r, id, cur_or_pre);
        if (l_res == -1) {
            return -1;
        }
        int r_res = find_id(tr[u].rc, M + 1, R, l, r, id, cur_or_pre);
        if (r_res == -1 || l_res != r_res) {
            return -1;
        }
        return l_res;
    }

    bool detect(int l, int r, int id, bool cur_or_pre) {
        return find_id(rt, interval_L, interval_R, l, r, id, cur_or_pre) == id;
    }

    void _erase(int u, int L, int R, int l, int r) {
        if (R < l || L > r) {
            return;
        }
        if (l <= L && R <= r) {
            tr[u].info.pre_id = tr[u].info.id, tr[u].info.id = 0;
            tr[u].info.tag_id = tr[u].info.tag_pre = 1;
            return;
        }
        pushdown(u);
        int M = (L + R) >> 1;
        _erase(tr[u].lc, L, M, l, r);
        _erase(tr[u].rc, M + 1, R, l, r);
        pushup(u);
    }

    void erase(int l, int r) {
        _erase(rt, interval_L, interval_R, l, r);
    }

    bool erase_real(int l, int r, int id) {
        bool flag = detect(l, r, id, true);
        if (flag) {
            erase(l, r);
        }
        return flag;
    }

    void _restore(int u, int L, int R, int l, int r) {
        if (R < l || L > r) {
            return;
        }
        if (l <= L && R <= r) {
            tr[u].info.id = tr[u].info.pre_id;
            tr[u].info.tag_id = 1;
            return;
        }
        pushdown(u);
        int M = (L + R) >> 1;
        _restore(tr[u].lc, L, M, l, r);
        _restore(tr[u].rc, M + 1, R, l, r);
        pushup(u);
    }

    void restore(int l, int r) {
        _restore(rt, interval_L, interval_R, l, r);
    }

    bool restore_real(int l, int r, int id) {
        bool flag = detect(l, r, id, false);
        if (flag) {
            restore(l, r);
        }
        return flag;
    }

    pair<int, int> _query(int u, int L, int R, int pos) {
        if (L == R) {
            return make_pair(tr[u].info.id, tr[u].info.id > 0 ? tr[u].info.val : 0);
        }
        pushdown(u);
        int M = (L + R) >> 1;
        if (M >= pos) {
            return _query(tr[u].lc, L, M, pos);
        } else {
            return _query(tr[u].rc, M + 1, R, pos);
        }
    }

    pair<int, int> query(int pos) {
        return _query(rt, interval_L, interval_R, pos);
    }
};

int main(int argc, char const *argv[]) {

    int n = rd(), m = rd(), k = rd(), op = 0, l = 0, r = 0, id = 0, x = 0, pos = 0;
    dynamic_segment_tree seg_tree = dynamic_segment_tree(1, m);
    pair<int, int> res;
    while (k--) {
        op = rd();
        switch (op) {
            case 0:
                id = rd(), l = rd(), r = rd(), x = rd();
                wr(seg_tree.set_real(l, r, id, x)), putchar('\n');
                break;
            case 1:
                id = rd(), l = rd(), r = rd();
                puts(seg_tree.erase_real(l, r, id) ? "OK" : "FAIL");
                break;
            case 2:
                id = rd(), l = rd(), r = rd();
                puts(seg_tree.restore_real(l, r, id) ? "OK" : "FAIL");
                break;
            case 3:
                pos = rd();
                res = seg_tree.query(pos);
                wr(res.first), putchar(' '), wr(res.second), putchar('\n');
            default:
                break;
        }
    }

    return 0;
}