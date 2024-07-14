/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-12 17:13:29
 * 	modified: 	2024-07-14 10:51:10
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll mod = 998244353;

ll powmod(ll a, ll b) {
	ll res = 1;
	a %= mod;
	assert(b >= 0);
	for (; b; b >>= 1) {
		if (b & 1) {
			res = res * a % mod;
		}
		a = a * a % mod;
	}
	return res;
}
// head

int _, n;
namespace linear_seq {
	const int N = 100010;
	ll res[N], base[N], _c[N], _md[N];
	vector<int> Md;
	void mul(ll *a, ll *b, int k) {
		for (int i = 0; i < k + k; i++) {
			_c[i] = 0;
		}
		for (int i = 0; i < k; i++) {
			if (a[i]) {
				for (int j = 0; j < k; j++) {
					_c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
				}
			}
		}
		for (int i = k + k - 1; i >= k; i--) {
			if (_c[i]) {
				for (int j = 0; j < (int)Md.size(); j++) {
					_c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
				}
			}
		}
		for (int i = 0; i < k; i++) {
			a[i] = _c[i];
		}
	}
	int solve(ll n, vector<int> a, vector<int> b) {
		// a 系数 b 初值 b[n+1]=a[0]*b[n]+...
		ll ans = 0, pnt = 0;
		int k = (int)a.size();
		assert((int)a.size() == (int)b.size());
		for (int i = 0; i < k; i++) {
			_md[k - 1 - i] = -a[i];
		}
		_md[k] = 1;
		Md.clear();
		for (int i = 0; i < k; i++) {
			if (_md[i] != 0) {
				Md.push_back(i);
			}
		}
		for (int i = 0; i < k; i++) {
			res[i] = base[i] = 0;
		}
		res[0] = 1;
		while ((1ll << pnt) <= n) {
			pnt++;
		}
		for (int p = pnt; p >= 0; p--) {
			mul(res, res, k);
			if ((n >> p) & 1) {
				for (int i = k - 1; i >= 0; i--) {
					res[i + 1] = res[i];
				}
				res[0] = 0;
				for (int j = 0; j < (int)Md.size(); j++) {
					res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
				}
			}
		}
		for (int i = 0; i < k; i++) {
			ans = (ans + res[i] * b[i]) % mod;
		}
		if (ans < 0) {
			ans += mod;
		}
		return ans;
	}
	vector<int> BM(vector<int> s) {
		vector<int> C(1, 1), B(1, 1);
		int L = 0, m = 1, b = 1;
		for (int n = 0; n < (int)s.size(); n++) {
			ll d = 0;
			for (int i = 0; i < L + 1; i++) {
				d = (d + (ll)C[i] * s[n - i]) % mod;
			}
			if (d == 0) {
				++m;
			} else if (2 * L <= n) {
				vector<int> T = C;
				ll c = mod - d * powmod(b, mod - 2) % mod;
				while ((int)C.size() < (int)B.size() + m) {
					C.push_back(0);
				}
				for (int i = 0; i < (int)B.size(); i++) {
					C[i + m] = (C[i + m] + c * B[i]) % mod;
				}
				L = n + 1 - L;
				B = T;
				b = d;
				m = 1;
			} else {
				ll c = mod - d * powmod(b, mod - 2) % mod;
				while ((int)C.size() < (int)B.size() + m) {
					C.push_back(0);
				}
				for (int i = 0; i < (int)B.size(); i++) {
					C[i + m] = (C[i + m] + c * B[i]) % mod;
				}
				++m;
			}
		}
		return C;
	}
	int gao(vector<int> a, ll n) {
		vector<int> c = BM(a);
		c.erase(c.begin());
		for (int i = 0; i < (int)c.size(); i++) {
			c[i] = (mod - c[i]) % mod;
		}
		return solve(n, c, vector<int>(a.begin(), a.begin() + (int)c.size()));
	}
}; // namespace linear_seq

int main(int argc, char const *argv[]) {

	ll m, l, r;
	cin >> m >> l >> r;
	vector<ll> k(m + 1);
	for (ll i = 0; i < m; i++) {
		cin >> k[i + 1];
	}
	int n = 30;
	vector<ll> a(n + 1);
	a[0] = 1;
	for (ll i = 1; i <= n; i++) {
		ll t = min(i, m);
		for (ll j = 1; j <= t; j++) {
			a[i] += k[j] * a[i - j];
			a[i] %= mod;
		}
	}
	vector<int> v;
	for (int i = 1; i <= n; i++) {
		v.emplace_back(a[i]);
	}
	for (int i = l; i <= r; i++) {
		cout << linear_seq::gao(v, i - 1) << "\n";
	}

	return 0;
}