/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-24 15:56:44
 * 	modified: 	2024-07-24 16:09:10
 * 	item: 		Certified Software Professional
 * 	site: 		92, Yugan
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, a, b;
    cin >> n >> a >> b;
    pair<int, int> u[a], v[b];
    for (int i = 0; i < a; i++) {
        cin >> u[i].first >> u[i].second;
    }
    for (int i = 0; i < b; i++) {
        cin >> v[i].first >> v[i].second;
    }
    long long res = 0;
    for (int i = 0, j = 0; i < a && j < b; i++) {
        while (j < b && v[j].first < u[i].first) {
            ++j;
        }
        if (j < b && v[j].first == u[i].first) {
            res += (long long)u[i].second * v[j].second;
        }
    }
    cout << res << "\n";

    return 0;
}