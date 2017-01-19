#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>

#define MAX 120000
#define LOG 17

typedef long long int_t;

struct  T {
	int to, c;
};

class Tree {
private:
	bool vis[MAX];
	int  cnt;
	void dfs(int x) {
		vis[x] = true;
		start[x] = ++cnt;
		for (size_t i = 0; i < m[x].size(); i++) {
			int to = m[x][i].to;
			if (vis[to]) continue;
			parent[to][0] = x;
			value[to][0] = m[x][i].c;
			dep[to] = dep[x] + 1;
			dfs(to);
		}
		end[x] = cnt;
	}
public:
	int parent[MAX][LOG + 1];
	int dfn[MAX];
	int dep[MAX];
	int start[MAX];
	int end[MAX];
	int_t value[MAX][LOG + 1];
	
	std::vector<T> m[MAX];

	void Create() {
		dfs(1);
	}
};


