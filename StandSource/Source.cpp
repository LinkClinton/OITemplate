#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

#define maxn (230)
int n, r, d[maxn]; double p[maxn], P[maxn], ans, f[maxn][maxn], ci[maxn][maxn];

inline void dp()
{
	for (int i = 1; i <= n; ++i)
	{
		ci[i][0] = 1;
		for (int j = 1; j <= r; ++j) ci[i][j] = ci[i][j - 1] * (1 - p[i]);
	}
	memset(f, 0, sizeof(f)); memset(P, 0, sizeof(P));
	f[0][r] = 1;
	for (int i = 0; i < n; ++i)
		for (int j = r; j >= r - i&&j >= 0; --j)
		{
			f[i + 1][j] += f[i][j] * ci[i + 1][j];
			if (j)
			{
				double t = f[i][j] * (1 - ci[i + 1][j]);
				f[i + 1][j - 1] += t; P[i + 1] += t;
			}
		}
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &n, &r);
		for (int i = 1; i <= n; ++i) scanf("%lf %d", p + i, d + i);
		dp(); ans = 0;
		for (int i = 1; i <= n; ++i) ans += P[i] * d[i];
		printf("%.10lf\n", ans);
	}
	fclose(stdin); fclose(stdout);
	return 0;
}