/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-20 08:44:25
 * 	modified: 	2024-07-13 10:34:28
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
/*
Game Theroy
1. minimax search
2. alpha-beta pruning
*/
#include <climits>
#include <iostream>

using namespace std;

int t[3][3], ept; // table, empty

bool judge(int f) {
	for (int i = 0; i < 3; i++) {
		if (t[i][0] == f && t[i][0] == t[i][1] && t[i][1] == t[i][2]) { // row
			return true;
		}
		if (t[0][i] == f && t[0][i] == t[1][i] && t[1][i] == t[2][i]) { // column
			return true;
		}
	}
	if (t[0][0] == f && t[0][0] == t[1][1] && t[1][1] == t[2][2]) { // main diagonal
		return true;
	}
	if (t[0][2] == f && t[0][2] == t[1][1] && t[1][1] == t[2][0]) { // secondary diagonal
		return true;
	}
	return false;
}

int iswin(int f) {
	if (!judge(f)) { // tie
		return 0;
	}
	return f == 1 ? (1 + ept) : -(1 + ept);
}

int dfs(int f) {
	if (ept == 0) {
		return 0;
	}
	int a = INT_MIN, b = INT_MAX; // minimax search
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (t[i][j] != 0) {
				continue;
			}
			t[i][j] = f;
			--ept;
			int w = iswin(f);
			if (w != 0) {
				// restore
				t[i][j] = 0;
				++ept;
				return f == 1 ? a = max(a, w) : b = min(b, w);
			}
			f == 1 ? a = max(a, dfs(2)) : b = min(b, dfs(1)); // alternate
			// restore
			t[i][j] = 0;
			++ept;
		}
	}
	return f == 1 ? a : b;
}

int main(int argc, char const *argv[]) {

	int tt;
	cin >> tt;
	for (int q = 0; q < tt; q++) {
		ept = 9;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> t[i][j];
				if (t[i][j] != 0) {
					--ept;
				}
			}
		}
		if (iswin(1) != 0) {
			cout << iswin(1) << "\n";
			continue;
		}
		if (iswin(2) != 0) {
			cout << iswin(2) << "\n";
			continue;
		}
		cout << dfs(1) << "\n";
	}

	return 0;
}