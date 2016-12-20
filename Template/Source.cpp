#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#define MAX 16007

int N, M;

namespace TwoSat {
	std::vector<int> m[MAX];
	std::vector<int> new_m[MAX];

	std::vector<int> set;

	int  dfn[MAX];
	int  low[MAX];
	int  belong[MAX];
	int  cnt = 0;
	int  g_cnt = 0;
	bool InStack[MAX];
	std::stack<int> Stack;

	void Tarjan(int x) {
		dfn[x] = low[x] = ++cnt;
		InStack[x] = true;
		Stack.push(x);

		for (size_t i = 0; i < m[x].size(); i++) {
			int to = m[x][i];
			if (!dfn[to]) {
				Tarjan(to);
				low[x] = std::min(low[x], low[to]);
			}
			else if (InStack[to]) low[x] = std::min(low[x], dfn[to]);
		}

		if (low[x] == dfn[x]) {
			g_cnt++;
			while (true) {
				int p = Stack.top(); Stack.pop();
				InStack[p] = false;
				belong[p] = g_cnt;
				if (p == x) break;
			}
		}
	}

	int In[MAX];

	int lazy[MAX];

	void del(int x) {
		if (lazy[x] != 0) return;
		lazy[x] = -1;
		for (size_t i = 0; i < new_m[x].size(); i++) {
			int to = new_m[x][i];
			if (lazy[to] != 0) continue;
			del(to);
		}
	}


	int Other[MAX];

	void Main() {
		for (int i = 0; i < N * 2; i++) {
			if (!dfn[i]) Tarjan(i);
		}

		for (int i = 0; i < N * 2; i++) {
			if (belong[i] == belong[i ^ true]) { printf("NIE\n"); return; }
			Other[belong[i]] = belong[i ^ true];
		}

		for (int i = 0; i < N * 2; i++) {
			for (size_t j = 0; j < m[i].size(); j++) {
				int to = m[i][j];
				if (belong[i] == belong[to]) continue;
				new_m[belong[to]].push_back(belong[i]);
				In[belong[i]]++;
			}
		}

		std::queue<int> t;
		
		for (int i = 1; i <= g_cnt; i++)
			if (In[i] == 0)  t.push(i);

		while (!t.empty()) {
			int p = t.front(); t.pop();
			set.push_back(p);
			for (size_t i = 0; i < new_m[p].size(); i++) {
				int to = new_m[p][i];
				In[to]--;
				if (In[to] == 0) t.push(to);
			}
		}

		for (size_t i = 0; i < set.size(); i++) {
			if (lazy[set[i]] == 0) {
				lazy[set[i]] = 1;
				del(Other[set[i]]);
			}
		}

		for (int i = 0; i < 2 * N; i++) {
			if (lazy[belong[i]] != -1) printf("%d\n", i + 1);
		}


	}

	void Add(int from, int to) {
		m[from].push_back(to ^ true);
		m[to].push_back(from ^ true);
	}


}

void Initalize() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		TwoSat::Add(x - 1, y - 1);
	}
}

int main() {
	Initalize();
	TwoSat::Main();
}