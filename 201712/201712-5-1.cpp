/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-12 21:45:29
 * 	modified: 	2024-07-12 21:55:33
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// 60 points with Time Limit Exceeded
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;
const ll maxn = 1e5 + 10, mod = 1e18;

int p[maxn], w[maxn], f[maxn];
ll v[maxn], ans[maxn];

int main(int argc, char const *argv[]) {

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= n; i++) {
			cin >> p[i] >> w[i] >> v[i] >> f[i];
		}
		for (int i = n; i > 0; i--) {
			int s = p[i], d = w[i];
			while (s > 0) {
				ans[s] = max(ans[s], v[s] - (ll)(f[s] - d) * (f[s] - d) + ans[i]);
				d += w[s];
				s = p[s];
			}
		}
		ll res = 0;
		for (int i = 1; i <= n; i++) {
			res = (res + ans[i]) % mod;
		}
		cout << res << "\n";
	}

	return 0;
}