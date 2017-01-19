#include"StandSource.hpp"

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
typedef long long sint;
#define pii pair<int,int>
#define mp make_pair
#define deg 20
#define maxn 501000
#define inf 0x3f3f3f3f
#define INF (1ll<<40)
int getint()
{
	int res; char c;
	while (c = getchar(), c<'0' || c>'9');
	res = c - '0';
	while (c = getchar(), c >= '0'&&c <= '9')
		res = res * 10 + c - '0';
	return res;
}
struct node
{
	int u, v, next;
}tree[maxn];
int first[maxn], next[maxn], to[maxn], fa[maxn][deg];
sint dp[maxn];
int indexs, en, en2, pre[maxn], n, dfn[maxn], dep[maxn], num, T;
pii g[maxn];
int vis[maxn], meet[maxn], val[maxn], minn[maxn][deg];
void build(int a, int b, int c)
{
	en++;
	to[en] = b;
	val[en] = c;
	::next[en] = first[a];
	first[a] = en;
}
void add(int u, int v)
{
	en2++;
	tree[en2].v = v;
	if (vis[u] != T)
	{
		vis[u] = T;
		tree[en2].next = 0;
	}
	else
	{
		tree[en2].next = pre[u];
	}
	pre[u] = en2;
}
void dfs(int now)
{
	int v;
	indexs++;
	dfn[now] = indexs;
	for (int i = first[now]; i; i = ::next[i])
	{
		v = to[i];
		if (v == fa[now][0]) continue;
		fa[v][0] = now;
		minn[v][0] = val[i];
		for (int j = 1; j<deg; j++)
		{
			fa[v][j] = fa[fa[v][j - 1]][j - 1];
			minn[v][j] = min(minn[v][j - 1], minn[fa[v][j - 1]][j - 1]);
		}
		dep[v] = dep[now] + 1;
		dfs(v);
	}
}
int lca(int u, int v)
{
	if (dep[u]<dep[v]) swap(u, v);
	for (int i = 19; i >= 0; i--)
	{
		if (dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	}
	if (u == v)return v;
	for (int i = 19; i >= 0; i--)
		if (fa[u][i] != fa[v][i])
		{
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
int sta[maxn], top;
inline long long getmin(int x, int y)
{
	int ans = inf;
	if (dep[x]<dep[y]) swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (dep[fa[x][i]] >= dep[y])
		{
			ans = min(ans, minn[x][i]);
			x = fa[x][i];
		}
	if (x == y)return ans;
	for (int i = 19; i >= 0; i--)
		if (fa[x][i] != fa[y][i])
		{
			ans = min(ans, min(minn[x][i], minn[y][i]));
			x = fa[x][i], y = fa[y][i];
		}
	if (x != y)ans = min(ans, min(minn[x][0], minn[y][0]));
	return ans;
}
void dfs2(int x)
{
	int v;
	dp[x] = 0;
	if (vis[x] == T)
		for (int i = pre[x]; i; i = tree[i].next)
		{
			dfs2(v = tree[i].v);
			dp[x] += min(getmin(v, x), meet[v] == T ? inf : dp[v]);
		}
}
void virtree()
{
	sta[top = 1] = 1;
	for (int i = 1; i <= num; i++)
	{
		int j = g[i].second;
		int anc = lca(sta[top], j);
		for (; dep[anc]<dep[sta[top]];)
		{
			if (dep[sta[top - 1]] <= dep[anc])
			{
				int last = sta[top--];
				if (sta[top] != anc)sta[++top] = anc;
				add(anc, last);
				break;
			}
			add(sta[top - 1], sta[top]), top--;
		}
		if (sta[top] != j)sta[++top] = j;
	}
	for (; top;)add(sta[top - 1], sta[top]), top--;
}
void solve()
{
	int a, b, c;
	num = getint();
	for (int i = 1; i <= num; i++)
	{
		a = getint();
		g[i] = mp(dfn[a], a);
		meet[a] = T;
	}
	sort(g + 1, g + 1 + num);
	virtree();
	dfs2(1);
	printf("%lld\n", dp[1]);
}
int main()
{
	input::Open();
	output::Open();
	int a, b, c;
	n = getint();
	for (int i = 1; i<n; i++)
	{
		a = getint();
		b = getint();
		c = getint();
		build(a, b, c);
		build(b, a, c);
	}
	dep[1] = 1;
	dfs(1);
	int cas = getint();
	while (cas--)
	{
		T++; en2 = 0;
		solve();
	}
	return 0;
}
