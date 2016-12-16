#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#define MAX 1200
#define INF 12900000

int N, M;

int Start;
int End;

int K;

#define UNABLE -1

namespace KthPath {

	struct Edge {
		int from, to;
		int c;
		bool Is;
		Edge(int _from, int _to, int _c) {
			from = _from;
			to = _to;
			c = _c;
			Is = true;
		}
	};

	std::vector<Edge> edge;

	std::vector<int> new_m[MAX];

	std::vector<int> m[MAX];
	int p[MAX];

	namespace Dijkstra {

		struct Node {
			int dis, x;
			Node(int _dis, int _x) {
				dis = _dis;
				x = _x;
			}
			bool operator<(const Node &a)const {
				return dis > a.dis;
			}
		};

		int dis[MAX];
		int ord[MAX];

		void Main(int Start) {
			for (int i = 1; i <= N; i++) {
				dis[i] = INF;
				ord[i] = -1;
			}

			dis[Start] = 0;

			std::priority_queue<Node, std::vector<Node> > t;
			t.push(Node(dis[Start], Start));

			while (!t.empty()) {
				Node p = t.top(); t.pop();
				for (size_t i = 0; i < new_m[p.x].size(); i++) {
					int edge_id = new_m[p.x][i];
					int to = edge[edge_id].from;

					if (dis[to] > p.dis + edge[edge_id].c) {
						dis[to] = p.dis + edge[edge_id].c;
						ord[to] = edge_id;
						t.push(Node(dis[to], to));
					}

				}
			}

		}

	}

	void AddEdge(int from, int to, int c) {
		edge.push_back(Edge(from, to, c));
		new_m[to].push_back(edge.size() - 1);
	}

	void Initalize() {
		Dijkstra::Main(End);

		for (int i = 1; i <= N; i++) {
			if (Dijkstra::ord[i] == UNABLE) continue;

			p[i] = edge[Dijkstra::ord[i]].to;
			edge[Dijkstra::ord[i]].Is = false;
		}
		p[End] = 0;

		for (size_t i = 0; i < edge.size(); i++) {
			if (edge[i].Is == false) continue;
			m[edge[i].from].push_back(i);
		}

	}

	std::priority_queue<Dijkstra::Node, std::vector<Dijkstra::Node> > t;

	void Main() {

		Initalize();

		t.push(Dijkstra::Node(Dijkstra::dis[Start], Start));

		int count = 0;

		for (int i = 1; i <= K; i++) {
			if (t.empty()) break;
			Dijkstra::Node x = t.top(); t.pop();
			std::cout << x.dis << std::endl;
			count++;
			int now = x.x;
			while (now) {
				for (size_t i = 0; i < m[now].size(); i++) {
					int edge_id = m[now][i];
					int to = edge[edge_id].to;
					int off = edge[edge_id].c - (Dijkstra::dis[edge[edge_id].from] - Dijkstra::dis[edge[edge_id].to]);
					Dijkstra::Node new_p(x.dis + off, to);
					t.push(new_p);
				}
				now = p[now];
			}
		}

		for (int i = count + 1; i <= K; i++)
			std::cout << -1 << std::endl;

		//if (t.empty()) { return; }
		//std::cout << t.top().dis + Dijkstra::dis[Start] << std::endl;

	}




}


int main() {

}