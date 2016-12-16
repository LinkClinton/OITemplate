#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#define MAX 60000
#define INF 12000000

int N, M;

namespace Dinic {

	struct Edge {
		int from, to;
		int f;
		Edge(int _from, int _to, int _f) { from = _from; to = _to; f = _f; }
	};

	std::vector<Edge> edge;
	std::vector<int> m[MAX];

	int S, T;

	void AddEdge(int from, int to, int f) {
		edge.push_back(Edge(from, to, f));
		edge.push_back(Edge(to, from, 0));
		m[from].push_back(edge.size() - 2);
		m[to].push_back(edge.size() - 1);
	}

	int level[MAX];

#define UNABLE -1

	void bfs(int start) {
		for (int i = 1; i <= T; i++)
			level[i] = UNABLE;
		level[start] = 0;

		std::queue<int> t;
		t.push(start);

		while (!t.empty()) {
			int p = t.front(); t.pop();
			for (size_t i = 0; i < m[p].size(); i++) {
				int edge_id = m[p][i];
				int to = edge[edge_id].to;
				if (level[to] != UNABLE || edge[edge_id].f <= 0) continue;
				level[to] = level[p] + 1;
				t.push(to);
			}
		}

	}



	int dfs(int x, int f) {
		if (x == T)return f;
		int allf = f;
		for (size_t i = 0; i < m[x].size(); i++) {
			int edge_id = m[x][i];
			int to = edge[edge_id].to;
			if (level[x] + 1 != level[to] || edge[edge_id].f <= 0 || f <= 0) continue;
			int usef = dfs(to, std::min(f, edge[edge_id].f));
			edge[edge_id].f -= usef;
			edge[edge_id ^ true].f += usef;
			f -= usef;
		}
		return allf - f;
	}

	int ans = 0;

	void Main() {
		while (true) {
			bfs(S);
			if (level[T] == UNABLE) break;
			ans += dfs(S, INF);
		}
	}


}

int main() {

}