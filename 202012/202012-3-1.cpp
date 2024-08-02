// https://www.acwing.com/activity/content/code/content/984425
#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 2000010;

struct node {
    string name;
    int id, type; // type = 0: folder; type = 1: file
    mutable ll ld, lr;
    mutable ll sd, sr;
    bool operator<(const node &t) const {
        return name < t.name;
    }
};

set<node> son[maxn];
int idx;
string str;
bool F;
int U;
ll SZ;

vector<string> get(string str) {
    vector<string> res(1, "root");
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '/') {
            continue;
        }
        string s;
        int j = i;
        while (j < str.size() && str[j] != '/') {
            s += str[j++];
        }
        res.emplace_back(s);
        i = j - 1;
    }
    return res;
}

ll dfs_remove(vector<string> &t, int u, int p) {
    string name = t[u];
    if (son[p].count({name}) == 0) {
        return -1;
    }
    set<node>::iterator it = son[p].find({name});
    if (u == t.size() - 1) {
        if (it->type) {
            t[u] = "#file";
        }
        ll sz = it->sr;
        son[p].erase(it);
        return sz;
    }
    if (it->type) {
        return -1;
    }
    ll sz = dfs_remove(t, u + 1, it->id);
    if (sz >= 0) {
        it->sr -= sz;
        if (t[u + 1] == "#file") {
            it->sd -= sz;
        }
    }
    return sz;
}

bool dfs_create(vector<string> &t, int u, int p, ll sz) {
    string name = t[u];
    if (u == t.size() - 1) {
        if (son[p].count({name}) != 0) {
            set<node>::iterator it = son[p].find({name});
            if (it->type == 0) {
                return false;
            }
            SZ = dfs_remove(t, 0, 0);
            node cur{name, ++idx, 1, 0, 0, 0, sz};
            son[p].emplace(cur);
            return true;
        } else {
            node cur{name, ++idx, 1, 0, 0, 0, sz};
            son[p].emplace(cur);
            return true;
        }
    } else {
        if (!son[p].count({name})) {
            if (U == -1) {
                U = u;
            }
            node cur{name, ++idx, 0, 0, 0, 0, 0};
            son[p].emplace(cur);
        }
        set<node>::iterator it = son[p].find({name});
        if (it->type) {
            return false;
        }
        bool res = dfs_create(t, u + 1, it->id, sz);
        if (res) {
            it->sr += sz;
            if (u + 1 == t.size() - 1) {
                it->sd += sz;
            }
            if (it->lr && it->sr > it->lr) {
                F = false;
            }
            if (it->ld && it->sd > it->ld) {
                F = false;
            }
        }
        return res;
    }
}

bool create(string str, ll sz) {
    vector<string> t = get(str);
    F = true, U = -1, SZ = -1;
    bool res = dfs_create(t, 0, 0, sz);
    bool ans = res && F;
    if (res && !F) {
        vector<string> t = get(str);
        if (U != -1) {
            while (t.size() - 1 > U) {
                t.pop_back();
            }
        }
        dfs_remove(t, 0, 0);
        if (SZ != -1) {
            create(str, SZ);
        }
    }
    return ans;
}

bool update(string str, ll d, ll r) {
    vector<string> t = get(str);
    int p = 0;
    for (int i = 0; i < t.size(); i++) {
        string &s = t[i];
        set<node>::iterator it = son[p].find({s});
        if (it == son[p].end()) {
            return false;
        }
        if (it->type) {
            return false;
        }
        if (i == t.size() - 1) {
            if (d && d < it->sd) {
                return false;
            }
            if (r && r < it->sr) {
                return false;
            }
            it->ld = d, it->lr = r;
        }
        p = it->id;
    }
    return true;
}

int main(int argc, char const *argv[]) {

    int n;
    cin >> n;
    str = "/tmp";
    create(str, 1);
    vector<string> t = get(str);
    dfs_remove(t, 0, 0);
    while (n--) {
        char op[2];
        cin >> op;
        bool res;
        if (*op == 'C') {
            ll sz;
            cin >> str >> sz;
            res = create(str, sz);
        } else if (*op == 'R') {
            cin >> str;
            vector<string> t = get(str);
            dfs_remove(t, 0, 0);
            res = true;
        } else {
            ll d, r;
            cin >> str >> d >> r;
            res = update(str, d, r);
        }
        if (res) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }

    return 0;
}