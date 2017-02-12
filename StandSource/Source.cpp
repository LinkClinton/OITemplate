#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 40400
using namespace std;
struct Line {
	int type;
	int x, y1, y2, z;
	Line() {}
	Line(int _, int __, int ___, int ____, int _____) :
		type(_), x(__), y1(___), y2(____), z(_____) {}
	bool operator < (const Line &l) const
	{
		if (x != l.x)
			return x < l.x;
		return type > l.type;
	}
}lines[M << 2];
struct Query {
	int x, y, k, id;
	bool operator < (const Query &q) const
	{
		return x < q.x;
	}
}queries[M];
struct abcd {
	int to, next;
}table[M << 1];
int head[M], _tot;
int n, m, q, tot;
int dpt[M], fa[M][16], st[M], ed[M];
int ans[M];
void Add(int x, int y)
{
	table[++_tot].to = y;
	table[_tot].next = head[x];
	head[x] = _tot;
}
void DFS(int x)
{
	static int T;
	int i;
	dpt[x] = dpt[fa[x][0]] + 1;
	st[x] = ++T;
	for (i = head[x]; i; i = table[i].next)
		if (table[i].to != fa[x][0])
		{
			fa[table[i].to][0] = x;
			DFS(table[i].to);
		}
	ed[x] = T;
}
int LCA(int x, int y)
{
	int j;
	if (dpt[x]<dpt[y])
		swap(x, y);
	for (j = 15; ~j; j--)
		if (dpt[fa[x][j]] >= dpt[y])
			x = fa[x][j];
	if (x == y) return x;
	for (j = 15; ~j; j--)
		if (fa[x][j] != fa[y][j])
			x = fa[x][j], y = fa[y][j];
	return fa[x][0];
}
int Second_LCA(int x, int y)
{
	int j;
	for (j = 15; ~j; j--)
		if (dpt[fa[y][j]]>dpt[x])
			y = fa[y][j];
	return y;
}
void Insert_Rectangle(int x1, int x2, int y1, int y2, int z)
{
	lines[++tot] = Line(1, x1, y1, y2, z);
	lines[++tot] = Line(-1, x2 + 1, y1, y2, z);
}
struct Segtree {
	Segtree *ls, *rs;
	int cnt;
	void* operator new (size_t)
	{
		static Segtree *mempool, *C;
		if (C == mempool)
			mempool = (C = new Segtree[1 << 16]) + (1 << 16);
		C->ls = C->rs = 0x0;
		C->cnt = 0;
		return C++;
	}
	friend void Modify(Segtree *&p, int x, int y, int pos, int val)
	{
		int mid = x + y >> 1;
		if (!p) p = new Segtree;
		p->cnt += val;
		if (x == y)
			return;
		if (pos <= mid)
			Modify(p->ls, x, mid, pos, val);
		else
			Modify(p->rs, mid + 1, y, pos, val);
	}
	friend int Get_Kth(Segtree *stack[], int top, int x, int y, int k)
	{
		int i, mid = x + y >> 1, cnt = 0;
		if (x == y) return mid;
		for (i = 1; i <= top; i++)
			cnt += stack[i] && stack[i]->ls ? stack[i]->ls->cnt : 0;
		if (k <= cnt)
		{
			for (i = 1; i <= top; i++)
				stack[i] = stack[i] ? stack[i]->ls : 0x0;
			return Get_Kth(stack, top, x, mid, k);
		}
		else
		{
			for (i = 1; i <= top; i++)
				stack[i] = stack[i] ? stack[i]->rs : 0x0;
			return Get_Kth(stack, top, mid + 1, y, k - cnt);
		}
	}
};
namespace BIT {
	Segtree *c[M];
	void Update(int x, int pos, int val)
	{
		for (; x; x -= x&-x)
			Modify(c[x], 0, 1000000000, pos, val);
	}
	int Get_Kth(int x, int k)
	{
		static Segtree *stack[M]; int top;
		top = 0;
		for (; x <= n; x += x&-x)
			stack[++top] = c[x];
		return Get_Kth(stack, top, 0, 1000000000, k);
	}
}

#include"StandSource.hpp"

int main()
{
	input::Open();
	output::Open();
	using namespace BIT;
	int i, j, x, y, z;
	cin >> n >> m >> q;
	for (i = 1; i<n; i++)
	{
		scanf("%d%d", &x, &y);
		Add(x, y); Add(y, x);
	}
	DFS(1);
	for (j = 1; j <= 15; j++)
		for (i = 1; i <= n; i++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	for (i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		if (st[x]>st[y])
			swap(x, y);
		int lca = LCA(x, y);
		if (lca != x)
			Insert_Rectangle(st[x], ed[x], st[y], ed[y], z);
		else
		{
			int temp = Second_LCA(x, y);
			if (st[temp] != 1)
				Insert_Rectangle(1, st[temp] - 1, st[y], ed[y], z);
			if (ed[temp] != n)
				Insert_Rectangle(st[y], ed[y], ed[temp] + 1, n, z);
		}
	}
	sort(lines + 1, lines + tot + 1);
	for (i = 1; i <= q; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		if (st[x]>st[y])
			swap(x, y);
		queries[i].x = st[x];
		queries[i].y = st[y];
		queries[i].k = z;
		queries[i].id = i;
	}
	sort(queries + 1, queries + q + 1);
	for (j = 1, i = 1; i <= q; i++)
	{

		for (; j <= tot&&lines[j].x <= queries[i].x; j++)
			Update(lines[j].y1 - 1, lines[j].z, -lines[j].type),
			Update(lines[j].y2, lines[j].z, lines[j].type);

		ans[queries[i].id] = Get_Kth(queries[i].y, queries[i].k);

	}
	for (i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
	return 0;
}