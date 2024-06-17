/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-16 11:16:16
 * 	modified: 	2024-06-17 19:57:34
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int maxs = 110;

int tr[maxs][26], fail[maxs], idx = 0;
// tr: trie or transfer function
// fail: mis-match, longest suffix, as next in KMP
// idx: index of node in trie
int cnt[maxs]; // count pattern/patterns ended with the node
long long w[maxs][maxs], dp[maxs][maxs];
// weight or transition matrix: w[from node][to node] = added important magnitude
// dp[length of string][node that string ended with] = maximum important magnitude
// state transition: dp[i][j] = max(dp[i][j], dp[i - 1][k] + w[k][j]), 0 <= k <= idx

void insert(string s) { // insert pattern to trie
	int p = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		int t = s[i] - 'a';
		if (tr[p][t] == 0) {
			tr[p][t] = ++idx;
		}
		p = tr[p][t]; // pointer to end of pattern
	}
	++cnt[p]; // count of pattern ended with the node from root in trie
}

void ac() { // Aho-Corasick Automaton
	queue<int> q;
	for (int i = 0; i < 26; i++) {
		if (tr[0][i] != 0) {
			q.emplace(tr[0][i]);
		}
	}
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			int &p = tr[t][i];
			if (p != 0) {
				fail[p] = tr[fail[t]][i];
				cnt[p] += cnt[fail[p]];
				// count of patterns ended with the node, not noly from root in trie
				// patterns = pattern from root + pattern from fail
				// prefix sum: since the level order of BFS, fail had calculated
				q.emplace(p);
			} else {
				p = tr[fail[t]][i];
			}
		}
	}
}

void mul(long long a[][maxs], long long b[][maxs]) {
	long long temp[maxs][maxs];
	memset(temp, -0x3f, sizeof(temp));
	for (int i = 0; i <= idx; i++) {
		for (int j = 0; j <= idx; j++) {
			for (int k = 0; k <= idx; k++) {
				temp[i][j] = max(temp[i][j], a[i][k] + b[k][j]);
				// overload: multiplication-wise addition
			}
		}
	}
	memcpy(a, temp, sizeof(temp));
}

int main(int argc, char const *argv[]) {

	int n;
	long long m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		insert(s);
	}
	ac();
	memset(w, -0x3f, sizeof(w)); // not reachable: -inf
	for (int i = 0; i <= idx; i++) {
		for (int j = 0; j < 26; j++) {
			int k = tr[i][j];
			w[i][k] = max(w[i][k], (long long)cnt[k]);
			// maximum: multiple edge from the node to the next node
		}
	}
	// F(i) = {f[i][j], 0 <= j <= idx}: (row) vector
	// F(i) = F(i - 1) * w
	// *: just represent multiplication-wise addition
	// *: f[i][j] = max(f[i - 1][k] + w[k][j]), 0 <= k <= idx
	// => F(m) = F(0) * w^m: only need the first row (vector) and a matrix
	for (int i = 1; i <= idx; i++) { // dp[0][0] = 0
		dp[0][i] = -1e18;			 // not reachable: -inf
	}
	while (m != 0) {
		if (m & 1) {
			mul(dp, w);
		}
		mul(w, w);
		m >>= 1;
	}
	long long ans = 0; // ans = max(dp[m][k]), 0 <= k <= idx
	for (int i = 0; i <= idx; i++) {
		ans = max(ans, dp[0][i]); // only update the first row
	}
	cout << ans;

	return 0;
}