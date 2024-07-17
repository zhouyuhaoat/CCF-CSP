/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 15:37:13
 * 	modified: 	2024-07-15 20:13:08
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

struct order {
	int op, id; // operation; process id
	order(int op, int id) : op(op), id(id) {
	}
};

vector<queue<order>> q;
vector<bool> vis; // exclusive resource for process

bool dfs(int op, int id, int pid) { // pid: parent process id
	if (vis[id]) {
		// closed loop => deadlock
		return false;
	}
	vis[id] = true;
	while (!q[id].empty()) {
		auto t = q[id].front();
		if (t.op == op && t.id == pid) { // match
			// op & pid: search target; id: localize process
			vis[id] = false;
			q[id].pop();
			return true;
		} else if (dfs(t.op ^ 1, t.id, id)) { // mismatch: to next process
			// ^: XOR => send <-> receive
			q[id].pop(); // backtrack: to current process
		} else {
			return false;
		}
	}
	vis[id] = false;
	return pid == -1; // until current process is done
}

int main(int argc, char const *argv[]) {

	int T, n;
	cin >> T >> n;
	getchar();
	q.resize(n), vis.resize(n);
	while (T--) {
		for (int i = 0; i < n; i++) {
			// initialization: clear queue and vis
			q[i] = queue<order>(); // empty queue
			vis[i] = false;
			string s;
			getline(cin, s);
			stringstream ss(s);
			while (ss >> s) {
				if (s[0] == 'S') { // send -> 0
					q[i].emplace(0, stoi(s.substr(1)));
				} else { // receive -> 1
					q[i].emplace(1, stoi(s.substr(1)));
				}
				// process id: multi-bit
			}
		}
		bool deadlock = false;
		for (int i = 0; i < n; i++) {
			if (!dfs(-1, i, -1)) { // -1: no process
				deadlock = true;
				break;
			}
		}
		if (deadlock) {
			cout << "1\n";
		} else {
			cout << "0\n";
		}
	}

	return 0;
}