#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<stack>
#define MAX 1200


namespace Fleury {

	std::vector<int> Ans;
	std::vector<int> m[MAX];
	std::stack<int> Stack;

	void dfs(int x) {
		Stack.push(x);
		if (Stack.empty()) return;
		int to = m[x][m[x].size() - 1];
		m[x].pop_back();
		dfs(to);
	}

	void fleury(int start) {
		Stack.push(start);
		while (!Stack.empty()) {
			int p = Stack.top(); Stack.pop();
			if (m[p].empty()) Ans.push_back(p);
			else dfs(p);
		}
	}

}
int N;
//针对欧拉回路
namespace Euler {

	struct Edge {
		int  u, v;
		bool Is;
		int to(int x) { if (u == x) return v; return u; Is = false; }
	};
	
	std::vector<int> Ans;
	std::vector<Edge> edge;
	std::vector<int> m[MAX];

	void dfs(int x) {
		for (size_t i = 0; i < m[x].size(); i++) {
			int edge_id = m[x][i];
			if (edge[edge_id].Is) continue;
			dfs(edge[edge_id].to(x));
		}
		Ans.push_back(x);//downto
	}

	void Main() {
		for (int i = 1; i <= N; i++) {
			if (m[i].empty()) continue;
			dfs(i);
			break;
		}
	}
	

}
int main() {

}