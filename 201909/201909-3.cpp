/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 22:39:23
 * 	modified: 	2024-07-16 13:05:58
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

typedef unsigned char uc; // 8-bit: 0 ~ 255 = 2^8 - 1
const int maxn = 1080, maxm = 1920;

uc g[maxn][maxm][3]; // pixel with RGB

int get(char c) { // hex: char -> int
	if (c <= '9') {
		return c - '0';
	}
	return c - 'a' + 10;
}

char get(int x) { // hex: int -> char
	if (x <= 9) {
		return x + '0';
	}
	return x - 10 + 'A';
}

void print(string str) { // string == const char*
	for (int i = 0; i < (int)str.size(); i++) {
		// ASCII('\0') = 0
		cout << "\\x" << get(str[i] / 16) << get(str[i] % 16);
	}
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int m, n;
	cin >> m >> n;
	int p, q;
	cin >> p >> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			string s;
			cin >> s;
			if (s.size() == 2) { // #a
				int t = get(s[1]);
				for (int k = 0; k < 3; k++) {
					g[i][j][k] = t * 16 + t;
				}
			} else if (s.size() == 4) { // #abc
				for (int k = 0; k < 3; k++) {
					int t = get(s[1 + k]);
					g[i][j][k] = t * 16 + t;
				}
			} else { // #abcdef
				for (int k = 0; k < 3; k++) {
					g[i][j][k] = get(s[1 + k * 2]) * 16 + get(s[2 + k * 2]);
				}
			}
		}
	}
	int bg[3] = {0}; // background
	for (int i = 0; i < n / q; i++) {
		for (int j = 0; j < m / p; j++) {
			int cur[3] = {0}; // background of current block
			for (int x = 0; x < q; x++) {
				for (int y = 0; y < p; y++) {
					for (int z = 0; z < 3; z++) {
						// size: n * m -> q * p
						cur[z] += g[i * q + x][j * p + y][z];
					}
				}
			}
			cur[0] /= p * q, cur[1] /= p * q, cur[2] /= p * q; // average
			if (cur[0] == bg[0] && cur[1] == bg[1] && cur[2] == bg[2]) {
				; // pass: same as background
			} else if (cur[0] == 0 && cur[1] == 0 && cur[2] == 0) {
				print("\033[0m"); // black -> reset
			} else {
				char s[50];
				snprintf(s, 50, "\033[48;2;%d;%d;%dm", cur[0], cur[1], cur[2]);
				print(s);
			}
			bg[0] = cur[0], bg[1] = cur[1], bg[2] = cur[2];
			print(" ");
			// blank space displays block with background
			// escape sequence controls the background color
		}
		// new line or row
		if (bg[0] != 0 || bg[1] != 0 || bg[2] != 0) { // reset
			print("\033[0m");
			bg[0] = bg[1] = bg[2] = 0;
		}
		print("\n");
	}

	return 0;
}