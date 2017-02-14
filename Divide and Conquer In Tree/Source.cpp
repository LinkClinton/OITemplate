#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>

#define MAX 160000

struct T {
	int to;
	long long c;
	T(int _to = 0, long long _c = 0) { to = _to; c = _c; }

	static bool cmpto(const T &a, const T &b) {
		return a.to < b.to;
	}
	static bool cmpc(const T &a, const T &b) {
		return a.c < b.c;
	}
};

namespace Center {

#define INF 2100000

	std::vector<T>* m;
	int* f;
	int* siz;

	int ans;
	int ans_size;
	int ALL;

	void dfs(int x) {
		int max_son = 0;
		for (size_t i = 0; i < m[x].size(); i++) {
			if (f[x] == m[x][i].to) continue;
			dfs(m[x][i].to);
			max_son = std::max(max_son, siz[m[x][i].to]);
		}

		max_son = std::max(max_son, ALL - siz[x]);

		if (ans_size > max_son) {
			ans_size = max_son;
			ans = x;
		}
	}

	int getCenter(int x, std::vector<T>* m_, int* f_, int* siz_) {
		m = m_;
		f = f_;
		siz = siz_;

		ans_size = INF;
		ALL = siz[x];
		dfs(x);
		return ans;
	}
}

int N, Q, A;
int level[MAX];
std::vector<T> m[MAX];
int  f[MAX];
int  dis[MAX];
int  siz[MAX];
bool v[MAX];

void bulid(int x) {
	v[x] = true;
	siz[x] = 1;
	for (size_t i = 0; i < m[x].size(); i++) {
		int to = m[x][i].to;
		if (v[to]) continue;
		f[to] = x;
		bulid(to);
		siz[x] += siz[to];
	}
}

struct ChildTree {
	std::vector<T> pool;
};

std::vector<ChildTree> child[MAX];
std::vector<int> p[MAX];
std::vector<int> numchild[MAX];
std::vector<int> dist[MAX];

int root_in_dfs;
int num_in_dfs;

void dfs(int x, ChildTree &childtree) {
	siz[x] = 1;
	childtree.pool.push_back(T(level[x], dis[x]));
	p[x].push_back(root_in_dfs);
	dist[x].push_back(dis[x]);
	numchild[x].push_back(num_in_dfs);

	for (size_t i = 0; i < m[x].size(); i++) {
		int to = m[x][i].to;
		if (f[x] == to) continue;
		f[to] = x;
		dis[to] = dis[x] + (int)m[x][i].c;
		dfs(to, childtree);
		siz[x] += siz[to];
	}
}

void MainTree(int x) {
	int root = Center::getCenter(x, m, f, siz);

	siz[root] = 1;
	dis[root] = 0;
	f[root] = 0;
	child[root].resize(m[root].size());
	for (size_t i = 0; i < m[root].size(); i++) {
		int to = m[root][i].to;
		f[to] = root;
		dis[to] = (int)m[root][i].c;

		root_in_dfs = root;
		num_in_dfs = i;

		dfs(to, child[root][i]);
		siz[root] += siz[to];
	}

	for (size_t i = 0; i < m[root].size(); i++) {
		int to = m[root][i].to;
		for (size_t j = 0; j < m[to].size(); j++) {
			if (m[to][j].to == root) {
				m[to].erase(m[to].begin() + j);
				break;
			}
		}
	}

	for (size_t i = 0; i < m[root].size(); i++)
		MainTree(m[root][i].to);
}

//find child[x][num] 最后一个小于等于limit的位置
int find(int x, int num, int limit) {
	int l = 0;
	int r = child[x][num].pool.size() - 1;
	int mid = 0;
	while (l < r) {
		mid = (l + r) >> 1;
		if (child[x][num].pool[mid].to > limit) r = mid - 1;
		else l = mid + 1;
	}
	while (mid + 1 < (int)child[x][num].pool.size() && child[x][num].pool[mid + 1].to <= limit)
		mid++;
	while (mid >= 0 && child[x][num].pool[mid].to> limit) mid--;
	return mid;
}

long long getAns(int x, int l, int r) {
	long long ans = 0;
	for (size_t i = 0; i < p[x].size(); i++) {
		int root = p[x][i];
		for (size_t j = 0; j < child[root].size(); j++) {
			if (j == numchild[x][i]) continue;
			long long l_pos = find(root, j, l - 1);
			long long r_pos = find(root, j, r);
			long long count = r_pos - l_pos;
			if (l_pos == -1) l_pos = 0; else l_pos = child[root][j].pool[(int)l_pos].c;
			if (r_pos == -1) r_pos = 0; else r_pos = child[root][j].pool[(int)r_pos].c;
			ans += ((long long)dist[x][i] * count + r_pos - l_pos);
		}
		if (level[root] >= l && level[root] <= r) ans += dist[x][i];
	}
	for (size_t i = 0; i < child[x].size(); i++) {
		long long l_pos = find(x, i, l - 1);
		long long r_pos = find(x, i, r);
		if (l_pos == -1) l_pos = 0; else l_pos = child[x][i].pool[(int)l_pos].c;
		if (r_pos == -1) r_pos = 0; else r_pos = child[x][i].pool[(int)r_pos].c;
		ans += (r_pos - l_pos);
	}
	return ans;
}

void Initalize() {
	scanf("%d %d %d", &N, &Q, &A);
	for (int i = 1; i <= N; i++)
		scanf("%d", &level[i]);
	for (int i = 1; i < N; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		m[u].push_back(T(v, c));
		m[v].push_back(T(u, c));
	}
	bulid(1);
	MainTree(1);

	for (int i = 1; i <= N; i++) {
		for (size_t j = 0; j < child[i].size(); j++) {
			std::sort(child[i][j].pool.begin(), child[i][j].pool.end(), T::cmpto);
			for (size_t k = 1; k < child[i][j].pool.size(); k++)
				child[i][j].pool[k].c += child[i][j].pool[k - 1].c;
		}
	}
}

long long last_ans = 0;

int main() {
	Initalize();

	for (int i = 1; i <= Q; i++) {
		int u, a, b;
		scanf("%d %d %d", &u, &a, &b);
		long long L, R;
		if (i == 1) {
			L = std::min(a%A, b%A);
			R = std::max(a%A, b%A);
		}
		else {
			L = std::min((a + last_ans) % A, (b + last_ans) % A);
			R = std::max((a + last_ans) % A, (b + last_ans) % A);
		}
		last_ans = getAns(u, L, R);
		printf("%lld\n", last_ans);
	}
}