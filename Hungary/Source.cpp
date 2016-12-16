/*
* 匈牙利算法，用来求二分图的最大匹配的。
* 对于一个点，如果他匹配的点已经有点被匹配了，那么如果那个占了这个点匹配的点，还能够再匹配到另外的点。
* 那么我们就交换匹配的点。
*/
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#define MAX 22000
#define INF 1200000
#define Unable -1

struct T {
	int to, c;
	T(int _to, int _c) { to = _to; c = _c; }
	static bool cmp(const T &a, const T &b) {
		return a.to < b.to;
	}
};

struct Edge {
	int from, to;
	int c;
	Edge(int _from, int _to, int _c) { from = _from; to = _to; c = _c; }
};

int N;
int arr[MAX];

std::vector<int> m[MAX];

namespace Hungary {

	int v[MAX];
	int target[MAX];
	int other[MAX];
	int ans;

	void AddEdge(int from, int to) {
		from++;
		to++;
		m[from].push_back(to);
	}

	bool dfs(int x) {
		v[x] = true;
		for (size_t i = 0; i < m[x].size(); i++) {
			int to = m[x][i];
			if (v[target[to]]) continue;
			if (target[to] == 0 || dfs(target[to])) {
				target[to] = x;
				other[x] = to;
				return true;
			}
		}
		return false;
	}

	void Main() {
		for (int i = 1; i <= N; i++)
			std::sort(m[i].begin(), m[i].end());
		memset(target, 0, sizeof(target));
		ans = 0;
		for (int i = N; i > 0; i--) {
			memset(v, false, sizeof(v));
			if (dfs(i)) ans++;
		}
	}

}

void Initalize() {
	std::scanf("%d", &N);
	for (int i = 0; i < N; i++)
		std::scanf("%d", &arr[i]);

	for (int i = 0; i < N; i++) {

		if (arr[i] == 0) { Hungary::AddEdge(i, i + N); continue; }
		//x>y and |x-y|=arr[i]
		if (i >= arr[i]) {
			int target = i - arr[i];
			int other = N - (i - target);
			if (arr[i] <= other) Hungary::AddEdge(i, target + N);
		}
		//x<y and |x-y|=arr[i]
		if (i + arr[i] < N) {
			int target = i + arr[i];
			int other = (N - (target - i));
			if (arr[i] <= other) Hungary::AddEdge(i, target + N);
		}
		//x>y and N-|x-y|=arr[i]
		if (arr[i] - N + i >= 0 && arr[i] - N + i < i) {
			int target = arr[i] - N + i;
			int other = i - target;
			if (arr[i] <= other) Hungary::AddEdge(i, target + N);
		}
		//x<y and N-|x-y|=arr[i] N-y+x=arr[i]
		if (N + i - arr[i] >= i && N + i - arr[i] < N) {
			int target = N + i - arr[i];
			int other = target - i;
			if (arr[i] <= other) Hungary::AddEdge(i, target + N);
		}
	}



}


int main() {
	Initalize();
	Hungary::Main();
	if (Hungary::ans != N) { printf("No Answer\n"); return 0; }
	for (int i = 1; i <= N; i++) {
		std::printf("%d", Hungary::other[i] - N - 1);
		if (i != N)
			std::printf(" ");
	}
	std::printf("\n");

}

