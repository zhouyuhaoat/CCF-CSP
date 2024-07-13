/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-13 10:48:16
 * 	modified: 	2024-07-13 19:05:04
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// https://www.acwing.com/solution/content/65978/
#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int N = 1e5 + 5, H = 18, inf = 1e9 + 7;
// ---------------------------------------------------------
void add(int &a, int b) {
	a += b;
	if (a > inf)
		a -= inf;
}
void mul(int &a, int b) {
	a = (ll)a * b % inf;
}
// ---------------------------------------------------------
// 树状数组，注意数组最大值 max_num 的使用
int tr[N], max_num;
void update(int from, int num) {
	for (; from <= max_num; from += from & -from)
		add(tr[from], num);
}
int sum(int from) {
	from = min(from, max_num);
	int res = 0;
	for (; from > 0; from -= from & -from)
		add(res, tr[from]);
	return res;
}
void clear() {
	for (int i = 1; i <= max_num; i++)
		tr[i] = 0;
}
// ---------------------------------------------------------
vector<int> vec[N];
bool vis[N];
pii q[N];
int sz[N], son[N]; // sz[]：子树大小，son[]：最大子树的大小
int getroot(int from) {
	int l = 0, r = 0;
	q[r++] = {from, 0};
	// 重点求出 sz 值，对该结点（包含）的所有子节点计数
	while (l < r) { // 队列正序
		pii &x = q[l++];
		sz[x.first] = son[x.first] = 1;
		for (int &p : vec[x.first])
			if (!vis[p] && p != x.second)
				q[r++] = {p, x.first};
	}
	int root = from;
	while (l) { // 队列逆序
		pii &x = q[--l];
		if (max(son[x.first], r - sz[x.first]) <= r >> 1)
			root = x.first;
		if (x.second)
			sz[x.second] += sz[x.first], son[x.second] = max(son[x.second], sz[x.first]);
	}
	return max_num = r, root; // 更新树状数组的最大值，返回重心
}
// ---------------------------------------------------------
int L, R;
int cnts[N], tmpcnts[N]; // cnts[] 为目标数组
int cntdep[N], dep[N];
void bfs(int from) {
	int l = 0, r = 0;
	q[r++] = {from, 0}, dep[from] = 2;
	while (l < r) {
		pii &x = q[l++];
		cntdep[dep[x.first]]++;
		tmpcnts[x.first] = sum(R - dep[x.first] + 1) - sum(L - dep[x.first]);
		if (dep[x.first] < R)
			for (int &p : vec[x.first])
				if (!vis[p] && p != x.second)
					dep[p] = dep[x.first] + 1, q[r++] = {p, x.first};
	}
	while (l) {
		pii &x = q[--l];
		add(cnts[x.first], tmpcnts[x.first]);
		if (x.second) // tmpcnts 要计入其所有的子孙节点
			add(tmpcnts[x.second], tmpcnts[x.first]);
	}
	for (int j = 2; cntdep[j]; j++)
		update(j, cntdep[j]), cntdep[j] = 0;
}
void build(int root) {
	vis[root] = 1, add(cnts[root], L == 1);
	clear(), update(1, 1); // 第一趟遍历计入以根为出发点的链
	for (int &p : vec[root])
		if (!vis[p]) // 第一趟遍历更新根节点
			bfs(p), add(cnts[root], tmpcnts[p]);
	clear();
	for (int i = vec[root].size() - 1; i >= 0; i--)
		if (!vis[vec[root][i]])
			bfs(vec[root][i]);
	for (int &p : vec[root])
		if (!vis[p])
			build(getroot(p));
}
// ---------------------------------------------------------
int depth[N], anc[N][H], s[N][H], n, m;
void buildlca(int lcaroot) {
	// 求 LCA 的辅助数组
	int l = 0, r = 0;
	q[r++] = {lcaroot, lcaroot}, depth[lcaroot] = 1;
	while (l < r) {
		pii &x = q[l++];
		anc[x.first][0] = x.second, s[x.first][0] = cnts[x.first];
		for (int &p : vec[x.first])
			if (p != x.second)
				depth[p] = depth[x.first] + 1, q[r++] = {p, x.first};
	}
	for (int i = 1; i != H; i++)
		for (int j = 1; j <= n; j++)
			anc[j][i] = anc[anc[j][i - 1]][i - 1], s[j][i] = s[j][i - 1], add(s[j][i], s[anc[j][i - 1]][i - 1]);
}
int calcu(int x, int y, int d) {
	// 用求 LCA 的方法求出 res 为需要更新的值
	if (depth[x] < depth[y])
		swap(x, y);
	int res = 0;
	for (int i = 0, h = depth[x] - depth[y]; h; h >>= 1, i++)
		if (h & 1)
			add(res, s[x][i]), x = anc[x][i];
	if (x == y)
		return add(res, s[x][0]), res;
	for (int i = H - 1; i >= 0; i--)
		if (anc[x][i] != anc[y][i])
			add(res, s[x][i]), add(res, s[y][i]), x = anc[x][i], y = anc[y][i];
	return add(res, s[x][0]), add(res, s[y][1]), res;
}
// ---------------------------------------------------------
int a[N], ans, T;
int main() { // 官网取消同步可以快 4s 左右
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0), cin >> T;
	while (T--) {
		cin >> n >> m >> L >> R;
		for (int i = 1; i <= n; i++)
			cin >> a[i], vec[i].clear(), cnts[i] = vis[i] = 0;
		for (int i = 2, num; i <= n; i++)
			// 用 vector 存边不是最快的方法，但是方便，且不会很大程度影响效率
			cin >> num, vec[i].push_back(num), vec[num].push_back(i);
		int lcaroot = getroot(1);
		ans = 0, build(lcaroot), buildlca(lcaroot);
		for (int i = 1; i <= n; i++)
			mul(a[i], cnts[i]), add(ans, a[i]);
		for (int x, y, d; m--;)
			cin >> x >> y >> d, mul(d, calcu(x, y, d)), add(ans, d), cout << ans << "\n";
	}
}