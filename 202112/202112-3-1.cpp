// https://www.acwing.com/solution/content/133709
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 1e5;

int st = 0, check;
int q[] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

vector<int> ma, mazi;
int mod = 929;
int g[maxn], d[maxn];
vector<int> g1, kd;

void trans_state(int new_st) {
    if (st == new_st) {
        return;
    }
    if (new_st == 0) {
        ma.emplace_back(28);
        if (st == 1) {
            ma.emplace_back(28);
        }
    } else if (new_st == 1) {
        ma.emplace_back(27);
    } else if (new_st == 2) {
        ma.emplace_back(28);
    }
    st = new_st;
}

void get_g() {
    g[0] = 1;
    int r = -3;
    for (int i = 1; i <= check; r = (3 * r) % mod, i++) {
        for (int j = i; j >= 1; j--) {
            g[j] = (g[j] * r + g[j - 1]) % mod;
        }
        g[0] = g[0] * r % mod;
    }
    for (int i = 0; i <= check; i++) {
        g1.emplace_back(g[i]);
    }
}

void get_kd() {
    for (int i = mazi.size() - 1, j = 0; i >= 0; i--, j++) {
        d[j + check] = mazi[i];
    }
    for (int i = 0; i < check + mazi.size(); i++) {
        kd.emplace_back(d[i]);
    }
}

int main(int argc, char const *argv[]) {

    int w, s;
    cin >> w >> s;
    string a;
    cin >> a;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] >= 'A' && a[i] <= 'Z') {
            trans_state(0);
            ma.emplace_back(a[i] - 'A');
        } else if (a[i] >= 'a' && a[i] <= 'z') {
            trans_state(1);
            ma.emplace_back(a[i] - 'a');
        } else {
            trans_state(2);
            ma.emplace_back(a[i] - '0');
        }
    }
    if (ma.size() % 2 == 1) {
        ma.emplace_back(29);
    }
    for (int i = 0; i < ma.size(); i += 2) {
        mazi.emplace_back(30 * ma[i] + ma[i + 1]);
    }
    check = q[s + 1];
    int all = 1 + mazi.size() + check;
    int pad;
    if (all % w == 0) {
        pad = 0;
    } else {
        pad = w - all % w;
    }
    for (int i = 0; i < pad; i++) {
        mazi.emplace_back(900);
    }
    int n = 1 + mazi.size();
    mazi.emplace(mazi.begin(), n);
    for (int i = 0; i < mazi.size(); i++) {
        cout << mazi[i] << "\n";
    }
    if (s != -1) {
        get_kd();
        get_g();
        for (int i = kd.size() - 1; i >= 0; i--) {
            int t = kd[i] / g1.back();
            int deta = i - g1.size() + 1;
            for (int j = g1.size() - 1; j >= 0 && deta >= 0; j--) {
                kd[j + deta] -= (t * g1[j]) % mod;
            }
        }
        for (int i = check - 1; i >= 0; i--) {
            cout << (-kd[i] % mod + mod) % mod << "\n";
        }
    }

    return 0;
}