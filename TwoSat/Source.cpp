#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#define MAX 20007

int N, M;

namespace TwoSat {


	std::vector<int> m[MAX];

	std::vector<int> set;

	bool v[MAX];


	int other(int x) {
		return x ^ true;
	}

	bool dfs(int x) {
		if (v[other(x)]) return false;
		if (v[x]) return true;
		v[x] = true;
		set.push_back(x);
		for (size_t i = 0; i < m[x].size(); i++) {
			if (!dfs(m[x][i])) return false;
		}
		return true;
	}

	bool noans = false;

	void Clear() {
		memset(v, false, sizeof(v));
		noans = false;
		set.clear();
		for (int i = 0; i <= N * 2; i++)
			m[i].clear();
	}

	void Main() {
		for (int i = 0; i < N; i++) {
			if (v[other(i * 2)] && v[i * 2]) { printf("die\n"); return; }
		}
		for (int i = 0; i < N; i++) {
			set.clear();
			if (!dfs(i * 2)) {
				for (size_t j = 0; j < set.size(); j++)
					v[set[j]] = false;
				set.clear();
				if (!dfs(other(i * 2)))
					noans = true;
			}
			if (noans) break;
		}
		if (noans) { printf("die\n"); return; }
		for (int i = 1; i <= 2 * N; i++) {
			if (v[i - 1] == true) {
				for (size_t j = 0; j < m[i - 1].size(); j++)
					if (v[m[i - 1][j]] == false) { printf("die\n"); return; }
			}
		}
		for (int i = 1; i <= 2 * N; i++)
			if (v[i - 1]) printf("%d ", i);
		printf("\n");
	}

	//i ,i=true
	void Case1(int i) {
		v[i] = true;
		//ok
	}
	//not i,i=false
	void Case2(int i) {
		v[other(i)] = true;
		//ok
	}
	//i and j,i=true and j=true
	void Case3(int i, int j) {
		v[i] = true;
		v[j] = true;
		//ok
	}
	//i and (not j),i=true and j=false
	void Case4(int i, int j) {
		v[i] = true;
		v[other(j)] = true;
		//ok
	}
	//i or j,i=true or j=true,
	//i=false j=true,j=false i=true
	void Case5(int i, int j) {
		m[other(i)].push_back(j);
		m[other(j)].push_back(i);
		//ok
	}
	//i or (not j),i=true or j=false
	//i=false j=false,j=true,i=true
	void Case6(int i, int j) {
		m[j].push_back(i);
		m[other(i)].push_back(other(j));
		//ok
	}
	//not (i and j),i=false or j=false
	//i=true j=false,j=true i=false
	void Case7(int i, int j) {
		m[i].push_back(other(j));
		m[j].push_back(other(i));
		//ok
	}
	//not (i or j) i=false and j=false
	void Case8(int i, int j) {
		v[other(i)] = true;
		v[other(j)] = true;
		//ok
	}
	//i xor j i!=j
	//i=false j=true,i=true j=false,j=true j=false,j=false i=true
	void Case9(int i, int j) {
		m[i].push_back(other(j));
		m[other(i)].push_back(j);
		m[j].push_back(other(i));
		m[other(j)].push_back(i);
		//ok
	}
	//not (i xor j) i==j
	//i=false j=false, i=true j=true
	void Case10(int i, int j) {
		m[i].push_back(j);
		m[j].push_back(i);
		m[other(i)].push_back(other(j));
		m[other(j)].push_back(other(i));
		//ok
	}
	//i xor (not j) i==j
	void Case11(int i, int j) {
		m[other(i)].push_back(other(j));
		m[other(j)].push_back(other(i));
		m[i].push_back(j);
		m[j].push_back(i);
		//ok
	}
	//(not i) or (not j) 
	//i=true j=false,j=true i=false
	void Case12(int i, int j) {
		m[i].push_back(other(j));
		m[j].push_back(other(i));
		//ok
	}
}



#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#define MAX 16007

int N, M;

namespace TwoSatM {
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
		TwoSatM::Add(x - 1, y - 1);
	}
}


int main() {

}