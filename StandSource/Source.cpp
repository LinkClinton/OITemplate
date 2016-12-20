#include <cstdio>
#define STDIN STDFILE()
void STDFILE() {
	freopen("C:/OI/Template/Template/T.in", "r", stdin);
	freopen("C:/OI/Template/Template/T.ans", "w", stdout);
}
#include<algorithm>
#define d1(i,x) for(int i=x;i;--i)
#define f1(i,x) for(int i=1;i<=x;++i)
#define f2(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N = 400010;
const int BUF = 13778000;
char Buf[BUF], *buf = Buf;
inline int read() { int a; for (a = 0; *buf<48; buf++); while (*buf>47)a = a * 10 + *buf++ - 48; return a; }
struct edge { int v, next; }b[1600005];
int n, m, x, y, k, c, t, sz, cnt;
int h[N], g[N], q[N], bl[N], pre[N]; bool p[N];
inline void ins(int u, int v, int*h) { b[++cnt] = { v,h[u] }; h[u] = cnt; }
inline void Ins(int u, int v) { ins(u, v, h); ins(v, u, g); }
inline void insert(int u, int v) { Ins(u, v); Ins(v ^ 1, u ^ 1); }
inline void dfs1(int x) { p[x] = 1; for (int e = h[x]; e; e = b[e].next)if (!p[b[e].v])dfs1(b[e].v); q[++t] = x; }
inline void dfs2(int x, int f) { p[x] = 0; bl[x] = f; for (int e = g[x]; e; e = b[e].next)if (p[b[e].v])dfs2(b[e].v, f); }
int main() {
	STDIN;
	fread(Buf, 1, BUF, stdin);
	n = read(); m = read();
	c = n + m + 1 << 1 | 1;
	f1(i, n)pre[i] = n + 1;
	f2(i, 2, m + 1) {
		x = read(); y = read(); k = read();
		insert(y << 1 | !k, pre[x] << 1);
		insert(n + i << 1, y << 1 | k);
		insert(n + i << 1, pre[x] << 1);
		pre[x] = n + i;
	}f1(i, n)insert(pre[i] << 1 | 1, i << 1);
	f2(i, 2, c)if (!p[i])dfs1(i);
	d1(i, t)if (p[q[i]])dfs2(q[i], ++sz); sz = 0;
	for (int i = 2; i<c; i += 2)if (bl[i] == bl[i ^ 1])return puts("Impossible"), 0;
	f1(i, n)if (bl[i << 1]>bl[i << 1 | 1])q[++sz] = i;
	printf("%d\n", sz); f1(i, sz)printf("%d ", q[i]);
}