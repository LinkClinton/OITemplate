#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

const int N = 100010;
struct node {
	int x, y, a, b, id;
	friend bool operator <(const node &a, const node &b) {
		if (a.a == b.a) return a.b<b.b;
		return a.a<b.a;
	}
	void init(int k) {
		id = k; scanf("%d%d%d%d", &x, &y, &a, &b);
	}
}e[N], q[N], tmp[N];
struct opt {
	int x, y, f, da, db, sz;
}op[N];
int ans[N], f[N], da[N], db[N], sz[N], Q, n, m, top, tot, x, y, S;

bool cmp(const node &a, const node &b) {
	if (a.b == b.b) return a.a<b.a;
	return a.b<b.b;
}
int find(int x) {
	return f[x] == x ? x : find(f[x]);
}
void merge(int x, int y, int a, int b) {
	x = find(x); y = find(y);
	if (sz[x]>sz[y]) swap(x, y);
	op[++tot].x = x; op[tot].da = da[y]; op[tot].db = db[y];
	op[tot].y = y; op[tot].f = f[x]; op[tot].sz = sz[y];
	if (x == y) {
		da[x] = max(da[x], a);
		db[x] = max(db[x], b);
		return;
	}
	f[x] = y; sz[y] += sz[x];
	da[y] = max(da[y], max(da[x], a));
	db[y] = max(db[y], max(db[x], b));
}
void Return() {
	for (; tot; tot--) {
		f[op[tot].x] = op[tot].f;
		db[op[tot].y] = op[tot].db;
		da[op[tot].y] = op[tot].da;
		sz[op[tot].y] = op[tot].sz;
	}
}
int main() {
	freopen("multiple.in", "r", stdin);
	freopen("multiple.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) e[i].init(i);
	sort(e + 1, e + 1 + m);
	S = (int)sqrt(m);
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) q[i].init(i);
	sort(q + 1, q + 1 + Q, cmp);
	for (int i = 1; i <= m; i += S) {
		top = 0;
		for (int j = 1; j <= Q; j++)
			if (q[j].a >= e[i].a && (i + S>m || q[j].a<e[i + S].a))
				tmp[++top] = q[j];
		sort(e + 1, e + i, cmp);
		for (int j = 1; j <= n; j++) f[j] = j, sz[j] = 1, da[j] = db[j] = -1;
		for (int j = 1, k = 1; j <= top; j++) {
			for (; k<i&&e[k].b <= tmp[j].b; k++)
				merge(e[k].x, e[k].y, e[k].a, e[k].b);
			tot = 0;
			for (int l = i; l<i + S&&l <= m; l++)
				if (e[l].a <= tmp[j].a&&e[l].b <= tmp[j].b)
					merge(e[l].x, e[l].y, e[l].a, e[l].b);
			x = find(tmp[j].x); y = find(tmp[j].y);
			ans[tmp[j].id] = x == y&&da[x] == tmp[j].a&&db[x] == tmp[j].b;
			Return();
		}
	}
	for (int i = 1; i <= Q; i++)
		if (ans[i]) puts("Yes");
		else puts("No");
		return 0;
}