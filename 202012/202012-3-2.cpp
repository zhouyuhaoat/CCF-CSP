// https://www.acwing.com/solution/content/41577
#include <iostream>
#include <map>
#include <queue>

using namespace std;

const int maxn = 2e6 + 5;

typedef long long ll;
typedef pair<ll, ll> pll;

string s[maxn];
int cnt, idx;

struct node {
    ll ld, lr, d, r, g;
    int id;
};

map<string, node> f[maxn];

void getp() {
    string str;
    cin >> str;
    int j = 0, len = str.size();
    cnt = 0;
    for (int i = 1; i < len; i++) {
        if (str[i] == '/') {
            s[++cnt] = str.substr(j + 1, i - j - 1), j = i;
        }
    }
    if (j != len - 1) {
        s[++cnt] = str.substr(j + 1, len - j - 1);
    }
    return;
}

ll find(int x, int k) {
    auto it = f[x].find(s[k]);
    if (it == f[x].end()) {
        return 0;
    }
    if (it != f[x].end()) {
        if (it->second.g) {
            return k == cnt ? it->second.g : -1;
        } else if (k == cnt) {
            return -1;
        } else {
            return find(it->second.id, k + 1);
        }
    }
}

bool create(int x, int k, ll val) {
    auto it = f[x].find(s[k]);
    if (k == cnt) {
        if (it != f[x].end()) {
            it->second.g += val;
        } else {
            f[x][s[k]] = {0, 0, 0, 0, val, ++idx};
        }
        return 1;
    }
    if (it == f[x].end()) {
        it = f[x].insert({s[k], {0, 0, 0, 0, 0, ++idx}}).first;
    }
    if (k == cnt - 1 && it->second.ld && it->second.ld < val + it->second.d) {
        return 0;
    }
    if (it->second.lr && it->second.lr < val + it->second.r) {
        return 0;
    }
    bool res = create(it->second.id, k + 1, val);
    if (res && (k == cnt - 1)) {
        it->second.d += val;
    }
    if (res) {
        it->second.r += val;
    }
    return res;
}

pll remove(int x, int k) {
    auto it = f[x].find(s[k]);
    if (it == f[x].end())
        return {0, 0};
    if (k == cnt) {
        queue<ll> q;
        q.emplace(it->second.id);
        while (!q.empty()) {
            for (auto y : f[q.front()]) {
                q.emplace(y.second.id);
            }
            f[q.front()].clear();
            q.pop();
        }
        f[x].erase(it);
        return {it->second.g, it->second.r + it->second.g};
    }
    pll cur = remove(it->second.id, k + 1);
    if (cur.first) {
        it->second.d -= cur.first, cur.first = 0;
    }
    it->second.r -= cur.second;
    return cur;
}

bool query(ll ld, ll lr) {
    for (ll k = 0, x = 0; k <= cnt; k++) {
        auto it = f[x].find(s[k]);
        if (it == f[x].end() || it->second.g)
            return false;
        if (k == cnt) {
            if ((ld && ld < it->second.d) || (lr && lr < it->second.r)) {
                return 0;
            }
            it->second.ld = ld;
            it->second.lr = lr;
        }
        x = it->second.id;
    }
    return true;
}

int main(int argc, char const *argv[]) {

    int n;
    cin >> n;
    f[0]["_root"] = node{0, 0, 0, 0, 0, ++idx};
    s[0] = "_root";
    while (n--) {
        char ch;
        cin >> ch;
        bool ans = 0;
        getp();
        if (ch == 'C') {
            ll w;
            cin >> w;
            ll res = find(0, 0);
            if (res != -1) {
                if (create(0, 0, w - res)) {
                    ans = 1;
                }
            }
        } else if (ch == 'R') {
            remove(0, 0);
            ans = 1;
        } else {
            ll ld, lr;
            cin >> ld >> lr;
            ans = query(ld, lr);
        }
        if (ans) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }

    return 0;
}