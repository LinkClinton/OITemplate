#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>

#define MAX 210

class UnionSet {
private:
	int f[MAX];
public:
	void resize(int n) {
		for (int i = 0; i <= n; i++)
			f[i] = i;
	}
	int Find(int x) {
		while (x != f[x]) x = f[x];
		return x;
	}
	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);
		f[y] = x;
	}
};

struct Edge {
	int u, v;
	int t, c;
	long long cost;
	Edge(int u_, int v_, int t_, int c_) { u = u_; v = v_; t = t_; c = c_; }
	static bool cmp(const Edge &a, const Edge &b) {
		return a.cost < b.cost;
	}
};

struct vec2 {
	int x, y;

	vec2(int x_ = 0, int y_ = 0) { x = x_; y = y_; }

	static int Cross(vec2 a, vec2 b) {
		return a.x*b.y - a.y*b.x;
	}
	long long getValue() {
		return (long long)x*(long long)y;
	}
};

std::vector<Edge> edge;
int N, M;

vec2 ans = vec2(1000000, 1000000);

vec2 MST() {

	std::sort(edge.begin(), edge.end(), Edge::cmp);
	UnionSet set;
	set.resize(N);

	int count = 1;
	vec2 result;

	for (size_t i = 0; i < edge.size(); i++) {
		int u = set.Find(edge[i].u);
		int v = set.Find(edge[i].v);
		if (u == v) continue;
		result.x += edge[i].t;
		result.y += edge[i].c;
		set.Union(u, v);
		count++;
		if (count == N) break;
	}

	if (ans.getValue() > result.getValue()) ans = result;
	if (ans.getValue() == result.getValue() && ans.y > result.y) ans = result;

	return result;
}

void Solve(vec2 A, vec2 B) {

	for (size_t i = 0; i < edge.size(); i++)
		edge[i].cost = edge[i].t*(A.y - B.y) + edge[i].c*(B.x - A.x);

	vec2 result = MST();

	if (vec2::Cross(vec2(result.x - A.x, result.y - A.y), vec2(result.x - B.x,
		result.y - B.y)) >= 0) return;

	Solve(A, result);
	Solve(result, B);
}

void Initalize() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++) {
		int u, v, c, t;
		scanf("%d %d %d %d", &u, &v, &c, &t);
		edge.push_back(Edge(u, v, t, c));
	}

	for (size_t i = 0; i < edge.size(); i++)
		edge[i].cost = edge[i].c;
	vec2 A = MST();
	for (size_t i = 0; i < edge.size(); i++)
		edge[i].cost = edge[i].t;
	vec2 B = MST();
	Solve(B, A);
}

int main() {
	Initalize();
	printf("%d %d\n", ans.y, ans.x);
}




