/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 09:29:53
 * 	modified: 	2024-07-15 14:36:10
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int ui; // binary representation

struct disk {
	vector<ui> block; // bytes
	bool flag = true; // dirty
};

void hexstr2block(string s, vector<ui> &block) { // hex string to binary
	for (size_t i = 0; i < s.size(); i += 8) {
		ui byte = 0;
		for (size_t j = 0; j < 8; j++) { // each char four bits
			char c = s[i + j];
			if (isdigit(c)) {
				byte = (byte << 4) + c - '0';
			} else {
				byte = (byte << 4) + toupper(c) - 'A' + 10;
			}
		}
		block.emplace_back(byte);
	}
}

string byte2hexstr(ui byte) {
	char buf[9]; // buffer with null terminator
	snprintf(buf, 9, "%08X", byte);
	// %08X: 8 hex digits, 0 padded
	return string(buf);
}

void XOR(vector<ui> &block1, vector<ui> &block2) { // eXclusive OR
	for (size_t i = 0; i < block1.size(); i++) {
		block1[i] ^= block2[i]; // bitwise
	}
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n, s, l;
	cin >> n >> s >> l;
	vector<disk> d(n);
	int notmiss;
	for (int i = 0; i < l; i++) {
		int id;
		string s;
		cin >> id >> s;
		hexstr2block(s, d[id].block);
		d[id].flag = false;
		notmiss = id;
	}
	if (l == n - 1) {
		vector<ui> block(d[notmiss].block.size(), 0); // all zero for XOR
		int miss = 0;
		for (int i = 0; i < n; i++) {
			if (d[i].flag) {
				miss = i;
				continue;
			}
			XOR(block, d[i].block);
		}
		d[miss].block = block, d[miss].flag = false;
	}
	int maxb = (n - 1) * d[notmiss].block.size(); // max block
	int m;
	cin >> m;
	while (m--) {
		int b;
		cin >> b;
		if (b >= maxb) {
			cout << "-\n";
			continue;
		}
		int dsk = b / s % n; // disk: column
		if (d[dsk].flag) {
			cout << "-\n";
			continue;
		}
		int stripe = b / ((n - 1) * s); // stripe: row
		// b % s: offset in stripe
		int blk = stripe * s + b % s; // block: row
		cout << byte2hexstr(d[dsk].block[blk]) << "\n";
	}

	return 0;
}