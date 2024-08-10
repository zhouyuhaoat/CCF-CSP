// https://www.acwing.com/activity/content/code/content/1155703
#include <iostream>

using namespace std;

const int maxn = 10010;

struct IP {
    int state;
    int t;
    string owner;
} ip[maxn];

void update(int tc, int n) {
    for (int i = 1; i <= n; i++) {
        if (ip[i].t != 0 && ip[i].t <= tc) {
            if (ip[i].state == 1) {
                ip[i] = {0, 0, ""};
            } else {
                ip[i] = {3, 0, ip[i].owner};
            }
        }
    }
}

int getbyowner(string client, int n) {
    for (int i = 1; i <= n; i++) {
        if (ip[i].owner == client) {
            return i;
        }
    }
    return 0;
}

int getbystate(int state, int n) {
    for (int i = 1; i <= n; i++) {
        if (ip[i].state == state) {
            return i;
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {

    int n, m, tdef, tmax, tmin;
    string h;
    cin >> n >> tdef >> tmax >> tmin >> h >> m;
    while (m--) {
        int tc;
        string client, server, type;
        int id, te;
        cin >> tc >> client >> server >> type >> id >> te;
        if (server != h && server != "*") {
            if (type != "REQ") {
                continue;
            }
        }
        if (type != "DIS" && type != "REQ") {
            continue;
        }
        if ((server == "*" && type != "DIS") || (server == h && type == "DIS")) {
            continue;
        }
        update(tc, n);
        if (type == "DIS") {
            int k = getbyowner(client, n);
            if (k == 0) {
                k = getbystate(0, n);
            }
            if (k == 0) {
                k = getbystate(3, n);
            }
            if (k == 0) {
                continue;
            }
            ip[k].state = 1, ip[k].owner = client;
            if (te == 0) {
                ip[k].t = tc + tdef;
            } else {
                int t = te - tc;
                t = max(t, tmin), t = min(t, tmax);
                ip[k].t = tc + t;
            }
            cout << h << " " << client << " " << "OFR" << " " << k << " " << ip[k].t << "\n";
        } else {
            if (server != h) {
                for (int i = 1; i <= n; i++) {
                    if (ip[i].owner == client && ip[i].state == 1) {
                        ip[i] = {0, 0, ""};
                    }
                }
                continue;
            }
            if (!(id >= 1 && id <= n && ip[id].owner == client)) {
                cout << h << " " << client << " " << "NAK" << " " << id << " " << 0 << "\n";
            } else {
                ip[id].state = 2;
                if (te == 0) {
                    ip[id].t = tc + tdef;
                } else {
                    int t = te - tc;
                    t = max(t, tmin), t = min(t, tmax);
                    ip[id].t = tc + t;
                }
                cout << h << " " << client << " " << "ACK" << " " << id << " " << ip[id].t << "\n";
            }
        }
    }

    return 0;
}