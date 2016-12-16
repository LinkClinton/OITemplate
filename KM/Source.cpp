#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define MAX 510
#define INF 100000002

int C[MAX][MAX];

int Nboy, NGirl;
int M;

namespace KM {

	int  target[MAX];
	int  other[MAX];

	int  boylazy[MAX];
	int  girllazy[MAX];

	bool visx[MAX];
	bool visy[MAX];

	int  lazy_min;

	int  boyset[MAX];
	int  girlset[MAX];
	int  boycnt;
	int  girlcnt;


	void AddEdge(int from, int to, int c) {
		C[from][to] = c;
	}

	bool dfs(int x) {
		if (visx[x]) return false;
		visx[x] = true;
		boyset[++boycnt] = x;
		for (int i = 1; i <= NGirl; i++) {
			if (visy[i]) continue;
			int d = boylazy[x] + girllazy[i] - C[x][i];
			if (d == 0) {
				visy[i] = true;
				girlset[++girlcnt] = i;
				if (target[i] == 0 || dfs(target[i])) {
					target[i] = x;
					other[x] = i;
					return true;
				}
			}
			else lazy_min = std::min(lazy_min, d);
		}
		return false;
	}

	void Main() {
		for (int i = 1; i <= Nboy; i++)
			for (int j = 1; j <= NGirl; j++)
				boylazy[i] = std::max(boylazy[i], C[i][j]);
		for (int i = 1; i <= NGirl; i++)
			girllazy[i] = 0;
		for (int i = 1; i <= Nboy; i++) {
			while (true) {
				memset(visx, false, sizeof(visx));
				memset(visy, false, sizeof(visy));
				lazy_min = INF;
				boycnt = 0;
				girlcnt = 0;
				if (dfs(i)) break;
				for (int j = 1; j <= boycnt; j++)
					boylazy[boyset[j]] -= lazy_min;
				for (int j = 1; j <= girlcnt; j++)
					girllazy[girlset[j]] += lazy_min;
			}
		}
	}
}

bool Swap;
int  Ans[MAX];

int read() {
	int x = 0;
	int f = 1;
	char ch = getchar();
	while (ch<'0' || ch>'9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0'&&ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x*f;
}

void Initalize() {
	Nboy = read();
	NGirl = read();
	M = read();
	for (int i = 1; i <= M; i++) {
		int u, v, c;
		u = read();
		v = read();
		c = read();
		if (Nboy <= NGirl)
			KM::AddEdge(u, v, c);
		else {
			KM::AddEdge(v, u, c);
		}
	}
	if (Nboy > NGirl) {
		std::swap(Nboy, NGirl);
		Swap = true;
	}
}
int main() {
	Initalize();
	KM::Main();
	long long ans = 0;
	for (int i = 1; i <= Nboy; i++) {
		ans += C[i][KM::other[i]];
	}
	printf("%lld\n", ans);
	if (!Swap) {
		for (int i = 1; i <= Nboy; i++) {
			if (C[i][KM::other[i]] == 0) printf("0 ");
			else printf("%d ", KM::other[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 1; i <= Nboy; i++) {
			if (C[i][KM::other[i]] != 0) Ans[KM::other[i]] = i;
		}
		for (int i = 1; i <= NGirl; i++)
			printf("%d ", Ans[i]);
		printf("\n");
	}
}
