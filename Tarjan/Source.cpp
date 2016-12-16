#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#define MAX 1200

struct Edge {
	int u, v;
	bool Is;
	Edge(int _u, int _v) { u = _u; v = _v;  Is = false; }
	int other(int x) { if (x == u) return v; return u; }
};

int N;

std::vector<Edge> edge;
std::vector<int> m[MAX];

namespace Tarjan {

	int  DFN[MAX];
	int  LOW[MAX];
	int  p[MAX];
	bool IsAns[MAX];
	
	int  cnt;

	void dfs(int x) {
		DFN[x] = LOW[x] = ++cnt;
		int Counter = 0;
		for (size_t i = 0; i < m[x].size(); i++) {
			int to = edge[m[x][i]].other(x);
			if (p[x] == to) continue;
			if (DFN[to] == 0) {
				p[to] = x;
				Counter++;
				dfs(to);
				LOW[x] = std::min(LOW[x], LOW[to]);

				if (p[x] == 0 && Counter >= 2) IsAns[x] = true;
				if (p[x] != 0 && LOW[to] >= DFN[x]) IsAns[x] = true;

				if (LOW[to] > DFN[x]) edge[m[x][i]].Is = true;
			}
			else LOW[x] = std::min(LOW[x], DFN[to]);
		}
	}

	void AddEdge(int u, int v) {
		edge.push_back(Edge(u, v));
		m[u].push_back(edge.size() - 1);
		m[v].push_back(edge.size() - 1);
	}

	void Initalize() {
		cnt = 0;
	}

	void Main() {
		for (int i = 1; i <= N; i++) {
			if (DFN[i] == 0) dfs(i);
		}
	}




}

int main() {

}