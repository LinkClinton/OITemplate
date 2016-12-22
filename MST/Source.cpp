#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#define MAX 51000
#define LOGN 18
//·ÅÆú¿¨³£ÁË

struct Edge {
	int u, v, c;
	int id;
	Edge() { u = 0; v = 0; c = 0; id = 0; }
	Edge(int _u, int _v, int _c, int _id) { u = _u; v = _v; c = _c; id = _id; }
};

int N, M, Q;

namespace UnionSet {
	int* f;
	int Find(int x) {
		if (x != f[x])
			return f[x] = Find(f[x]);
		return x;
	}
	void Merge(int u, int v) {
		u = Find(u);
		v = Find(v);
		f[u] = v;
	}

	void Initalize(int* relation) {
		f = relation;
	}
}

struct Problem {
	int edge_id;
	int new_value;
};

Problem problem[MAX];

Edge  edge_pool[MAX];
Edge* hash_edge[MAX];


bool edge_state[MAX];

static bool cmp(const Edge* a, const Edge* b) {
	return a->c < b->c;
}

class Graph {
public:
	Edge* edge[MAX];
	int f[21000];
	int tmp_f[21000];
	int ecount;


	void DeleteNotUsedEdge(int l, int r) {

		int count = 0;

		memcpy(tmp_f, f, sizeof(f));
		UnionSet::Initalize(tmp_f);
		for (size_t i = 1; i <= ecount; i++) {
			if (edge_state[edge[i]->id] == false) {
				int u = UnionSet::Find(edge[i]->u);
				int v = UnionSet::Find(edge[i]->v);
				if (u != v) {
					edge[++count] = edge[i];
					UnionSet::Merge(u, v);
				}
			}
			else edge[++count] = edge[i];
		}
		ecount = count;
	}

	void DeleteNotUsedPoint(int l, int r, long long &ans) {
		memcpy(tmp_f, f, sizeof(f));

		UnionSet::Initalize(tmp_f);
		for (int i = l; i <= r; i++) {
			int u = UnionSet::Find(edge_pool[problem[i].edge_id].u);
			int v = UnionSet::Find(edge_pool[problem[i].edge_id].v);
			if (u != v)
				UnionSet::Merge(u, v);
		}

		int count = 0;

		for (size_t i = 1; i <= ecount; i++) {
			if (edge_state[edge[i]->id] == true) { edge[++count] = edge[i]; continue; }
			int u = UnionSet::Find(edge[i]->v);
			int v = UnionSet::Find(edge[i]->u);
			if (u != v) {
				UnionSet::Merge(u, v);
				UnionSet::Initalize(f);
				UnionSet::Merge(edge[i]->u, edge[i]->v);
				ans += edge[i]->c;
				UnionSet::Initalize(tmp_f);
			}
			else
				edge[++count] = edge[i];
		}


		ecount = count;

	}

	void Run(int l, int r, long long& ans) {

		UnionSet::Initalize(f);
		for (size_t i = 1; i <= ecount; i++) {
			int u = UnionSet::Find(edge[i]->u);
			int v = UnionSet::Find(edge[i]->v);
			if (u != v) {
				UnionSet::Merge(u, v);
				ans += edge[i]->c;
			}
		}
	}

	void CopyTo(Graph* graph) {
		memcpy(graph->f, f, sizeof(f));
		for (int i = 1; i <= ecount; i++)
			graph->edge[i] = edge[i];
		graph->ecount = ecount;
	}
};

long long Ans[MAX];

Graph graph[LOGN];

int now_l = 0;
int now_r = 0;

void Solve(int l, int r, long long ans, int t) {
	int k = Q;
	if (l == r)
		edge_pool[problem[l].edge_id].c = problem[l].new_value;

	if (t != 1)
		graph[t - 1].CopyTo(&graph[t]);

	std::sort(graph[t].edge + 1, graph[t].edge + graph[t].ecount + 1, cmp);

	if (l == r) {
		graph[t].Run(l, r, ans);
		Ans[(l + r) >> 1] = ans;
		return;
	}

	for (int i = l; i <= r; i++)
		edge_state[problem[i].edge_id] = true;

	graph[t].DeleteNotUsedEdge(l, r);
	graph[t].DeleteNotUsedPoint(l, r, ans);

	for (int i = l; i <= r; i++)
		edge_state[problem[i].edge_id] = false;

	int mid = (l + r) >> 1;
	Solve(l, mid, ans, t + 1);
	Solve(mid + 1, r, ans, t + 1);

}

void Initalize() {
	scanf("%d %d %d", &N, &M, &Q);
	for (int i = 1; i <= M; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		edge_pool[i] = Edge(u, v, c, i);
		hash_edge[i] = &edge_pool[i];
	}

	std::sort(hash_edge + 1, hash_edge + 1 + M, cmp);

	for (int i = 1; i <= M; i++)
		graph[1].edge[i] = hash_edge[i];
	graph[1].ecount = M;

	for (int i = 1; i <= N; i++)
		graph[1].f[i] = i;


	for (int i = 1; i <= Q; i++)
		scanf("%d %d", &problem[i].edge_id, &problem[i].new_value);
}

int main() {
	//freopen("hnoi2010_city15.in", "r", stdin);
	//freopen("hnoi2010_city.out", "w", stdout);
	Initalize();
	Solve(1, Q, 0, 1);
	for (int i = 1; i <= Q; i++) {
		printf("%lld\n", Ans[i]);
	}
}