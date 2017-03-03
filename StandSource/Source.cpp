#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>

#define INF 1000000007
#define MAX 1000

int map[MAX][MAX];
char graph[40][40];

int m, n, k, h;
int p_count;
int p[MAX];

int all = 0;

int  dis[MAX];
bool v[MAX];

int ans = 0;

namespace SPFA {

	void Main(int Start) {
		int nm = n*m;
		for (int i = 1; i <= nm; i++) {
			dis[i] = INF;
			v[i] = false;
		}

		std::queue<int> t;
		dis[Start] = 0;
		v[Start] = true;

		t.push(Start);

		while (!t.empty()) {
			int p = t.front(); t.pop();
			v[p] = false;

			for (int to = 1; to <= nm; to++) {
				if (dis[to] > dis[p] + map[p][to]) {
					dis[to] = dis[p] + map[p][to];
					if (v[to] == false) {
						v[to] = true; t.push(to);
					}
				}
			}

		}
	}

}

int getID(int x, int y) {
	return (x - 1)*n + y;
}

void make_road(int i, int j) {
	int real_j = j - 1;
	if (i != 1 && graph[i - 1][real_j] != '#') map[getID(i, j)][getID(i - 1, j)] = 0;
	if (i != m && graph[i + 1][real_j] != '#') map[getID(i, j)][getID(i + 1, j)] = 0;
	if (j != 1 && graph[i][real_j - 1] != '#') map[getID(i, j)][getID(i, j - 1)] = 0;
	if (j != n && graph[i][real_j + 1] != '#') map[getID(i, j)][getID(i, j + 1)] = 0;
}

void make_damage(int i, int j, int damage) {
	if (i != 1) map[getID(i - 1, j)][getID(i, j)] = damage;
	if (i != m) map[getID(i + 1, j)][getID(i, j)] = damage;
	if (j != 1) map[getID(i, j - 1)][getID(i, j)] = damage;
	if (j != n) map[getID(i, j + 1)][getID(i, j)] = damage;
}

void make_state(int x) {
	int damage[10];
	for (int i = 1; i <= k; i++) {
		damage[i] = (x >> (i - 1) & 1);
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if ((graph[i][j - 1] - 'A' + 1) >= 1 && (graph[i][j - 1] - 'A' + 1) <= k) {
				make_damage(i, j, damage[graph[i][j - 1] - 'A' + 1]);
			}
		}
	}
}

int Start;
std::vector<int> End;

void readData() {
	scanf("%d %d %d %d", &m, &n, &k, &h);
	for (int i = 1; i <= m; i++) {
		scanf("%s", graph[i]);
	}
	for (int i = 1; i <= n*m; i++) {
		for (int j = 1; j <= n*m; j++) {
			if (i == j) continue; map[i][j] = INF;
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (graph[i][j - 1] != '#') {
				make_road(i, j);
				if (graph[i][j - 1] == '$') Start = getID(i, j);
				if (graph[i][j - 1] == '@') End.push_back(getID(i, j));
			}
		}
	}

	p_count = (int)std::pow(2, k);

	for (int i = 0; i < p_count; i++) {
		scanf("%d", &p[i]);
		all += p[i];

		make_state(i);
		SPFA::Main(Start);
		for (size_t j = 0; j < End.size(); j++) {
			if (dis[End[j]] < h - 1) { ans += p[i]; break; }
		}
	}
}

int main() {
	readData();
	double Ans = (double)ans / (double)all;
	printf("%lf\n", Ans);
}
